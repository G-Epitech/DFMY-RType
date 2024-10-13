/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "./server.hpp"

using namespace rtype::sdk::game::api;

Server::Server(int port)
    : logger_("serverAPI"), serverTCP_(port, [this](const abra::server::ClientTCPMessage &message) {
        return this->SystemTCPMessagesMiddleware(message);
      }) {
  this->InitTCP();
}

Server::~Server() {
  this->serverTCP_.Close();
  this->threadTCP_.join();

  logger_.Info("Server TCP thread stopped", "🛑");

  for (auto &lobby : this->lobbies_) {
    lobby.second.serverUDP->Close();
    lobby.second.thread.join();

    logger_.Info("Lobby [" + std::to_string(lobby.first) + "] UDP thread stopped", "🛑");
  }
}

std::uint64_t Server::CreateLobby(const std::string &name,
                                  const std::function<void(std::uint64_t)> &newPlayerHandler) {
  std::uint64_t lobbyId = this->lobbies_.size();
  std::uint64_t port = 30000 + lobbyId;

  this->newPlayerHandler_ = newPlayerHandler;

  this->lobbies_[lobbyId] = Lobby(
      {.id = lobbyId, .name = name, .serverUDP = std::make_unique<abra::server::ServerUDP>(port)});
  this->InitUDP(lobbyId);

  logger_.Info("Register new lobby [" + std::to_string(lobbyId) + "]", "🛃");
  return lobbyId;
}

void Server::InitTCP() {
  this->threadTCP_ = std::thread(&Server::ListenTCP, this);
  logger_.Info("Server TCP thread started", "🚀");
}

void Server::ListenTCP() {
  this->serverTCP_.Start();
}

void Server::InitUDP(std::uint64_t id) {
  this->lobbies_[id].thread = std::thread(&Server::ListenUDP, this, id);
  logger_.Info("Lobby [" + std::to_string(id) + "] UDP thread started", "🚀");
}

void Server::ListenUDP(std::uint64_t id) {
  this->lobbies_[id].serverUDP->Start();
}

bool Server::SystemTCPMessagesMiddleware(const abra::server::ClientTCPMessage &message) {
  if (handlers_.find(message.messageType) == handlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (middleware catch)", "🔧");
  (this->*(handlers_[message.messageType]))(message);

  return false;
}

void Server::HandleClientConnection(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::Connection>(message.bitset);
  auto pseudo = packet->GetPayload().pseudo;

  payload::ConnectionInfos connectionInfos = {
      .onlinePlayers = static_cast<unsigned int>(this->clients_.size()) + 1};

  this->SendPayloadTCP(MessageServerType::kConnectionInfos, connectionInfos, message.clientId);
  this->AddNewClient(message.clientId, pseudo);
}

void Server::AddNewClient(std::uint64_t clientId, const std::string &pseudo) {
  Client client = {.id = clientId, .pseudo = pseudo, .inLobby = false};

  this->clients_.push_back(client);
  logger_.Info("New client connected: " + pseudo, "👤");
}

void Server::HandleLobbyJoin(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::JoinLobby>(message.bitset);
  auto id = packet->GetPayload().lobbyId;

  if (this->lobbies_.find(id) == this->lobbies_.end()) {
    logger_.Warning("Try to join an invalid lobby", "🛃");
    return;
  }

  this->clients_[message.clientId].lobbyId = id;

  auto endpoint = this->lobbies_[id].serverUDP->GetEndpoint();
  payload::JoinLobbyInfos joinInfos{};

  const char *ipPtr = endpoint.ip.c_str();
  strncpy(joinInfos.ip, ipPtr, 16);
  joinInfos.port = endpoint.port;

  this->SendPayloadTCP(MessageServerType::kServerJoinLobbyInfos, joinInfos, message.clientId);
  logger_.Info(
      "Send lobby [" + std::to_string(id) + "] infos to client " + std::to_string(message.clientId),
      "🛃");
}

void Server::HandleLobbyAddPlayer(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::JoinLobbyInfos>(message.bitset);
  auto ip = packet->GetPayload().ip;
  auto port = packet->GetPayload().port;

  this->clients_[message.clientId].inLobby = true;
  this->clients_[message.clientId].endpoint =
      boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);

  auto lobbyId = this->clients_[message.clientId].lobbyId;
  this->lobbies_[lobbyId].clients.push_back({
      .id = message.clientId,
      .endpoint = this->clients_[message.clientId].endpoint,
  });

  this->newPlayerHandler_(message.clientId);

  logger_.Info("Client " + std::to_string(message.clientId) + " joined the lobby", "🛃");
}

std::queue<abra::server::ClientTCPMessage> Server::ExtractMainQueue() {
  return this->serverTCP_.ExtractQueue();
}

std::uint64_t Server::FindUserByEndpoint(std::uint64_t lobbyId,
                                         const boost::asio::ip::udp::endpoint &endpoint) {
  if (this->lobbies_.find(lobbyId) == this->lobbies_.end()) {
    logger_.Warning("Try to extract an invalid lobby queue", "🧟‍♂️");
    return 0;
  }

  for (auto &client : this->lobbies_[lobbyId].clients) {
    if (client.endpoint == endpoint) {
      return client.id;
    }
  }

  return 0;
}

std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> Server::ExtractLobbyQueue(
    std::uint64_t id) {
  if (this->lobbies_.find(id) == this->lobbies_.end()) {
    logger_.Warning("Try to extract an invalid lobby queue", "🧟‍♂️");
    return {};
  }

  auto queue = this->lobbies_[id].serverUDP->ExtractQueue();
  std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> extractedQueue;

  while (!queue.empty()) {
    auto message = queue.front();
    auto userId = this->FindUserByEndpoint(id, message.endpoint);

    extractedQueue.emplace(userId, queue.front());
    queue.pop();
  }

  return extractedQueue;
}

bool Server::SendPlayersState(const uint64_t &lobbyId,
                              const std::vector<payload::PlayerState> &state) {
  if (this->lobbies_.find(lobbyId) == this->lobbies_.end()) {
    logger_.Warning("Try send packets to invalid lobby queue", "🧟‍♂️");
    return {};
  }

  auto success = this->SendPayloadsToLobby(MessageServerType::kPlayersState, state, lobbyId);
  if (success) {
    this->logger_.Info("Players state sent to lobby " + std::to_string(lobbyId), "🦹🏽");
  }

  return success;
}

bool Server::SendEnemiesState(const uint64_t &lobbyId,
                              const std::vector<payload::EnemyState> &state) {
  if (this->lobbies_.find(lobbyId) == this->lobbies_.end()) {
    logger_.Warning("Try send packets to invalid lobby queue", "🧟‍♂️");
    return {};
  }

  auto success = this->SendPayloadsToLobby(MessageServerType::kEnemiesState, state, lobbyId);
  if (success) {
    this->logger_.Info("Enemies state sent to lobby " + std::to_string(lobbyId), "🧌");
  }

  return success;
}

bool Server::SendBulletsState(const uint64_t &lobbyId,
                              const std::vector<payload::BulletState> &state) {
  if (this->lobbies_.find(lobbyId) == this->lobbies_.end()) {
    logger_.Warning("Try send packets to invalid lobby queue", "🧟‍♂️");
    return {};
  }

  auto success = this->SendPayloadsToLobby(MessageServerType::kBulletsState, state, lobbyId);
  if (success) {
    this->logger_.Info("Bullets state sent to lobby " + std::to_string(lobbyId), "💥");
  }

  return success;
}
