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
        return this->SystemServerTCPMessagesMiddleware(message);
      }) {
  this->InitServerTCP();
}

Server::~Server() {
  this->serverTCP_.Close();
  this->threadTCP_.join();

  for (auto &lobby : this->lobbies_) {
    lobby.second.clientTCP->Close();
  }

  logger_.Info("Server TCP thread stopped", "🛑");
}

std::uint64_t Server::CreateLobby(const std::string &name, uint64_t port) {
  std::uint64_t lobbyId = this->lobbies_.size();
  auto clientTCP = std::make_unique<abra::client::ClientTCP>(
      kLocalhost, port, [this, lobbyId](const abra::tools::MessageProps &message) {
        return this->SystemClientTCPMessagesMiddleware(message, lobbyId);
      });

  this->lobbies_[lobbyId] =
      Lobby({.id = lobbyId, .name = name, .clientTCP = std::move(clientTCP), .enabled = false});

  payload::RegisterLobby registerPayload = {
      .lobbyId = static_cast<unsigned int>(lobbyId),
  };
  if (SendPayloadLobbyTCP(MessageServerType::kRegisterLobby, registerPayload, lobbyId)) {
    logger_.Info("Register new lobby [" + std::to_string(lobbyId) + "]", "🛃");
  }

  InitClientTCP(lobbyId);

  return lobbyId;
}

void Server::InitServerTCP() {
  this->threadTCP_ = std::thread(&Server::ListenServerTCP, this);
  logger_.Info("Server TCP thread started", "🚀");
}

void Server::ListenServerTCP() {
  this->serverTCP_.Start();
}

void Server::InitClientTCP(std::uint64_t id) {
  this->lobbies_[id].thread = std::thread(&Server::ListenClientTCP, this, id);
  logger_.Info("Server TCP thread started", "🚀");
}

void Server::ListenClientTCP(std::uint64_t id) {
  this->lobbies_[id].clientTCP->Listen();
}

bool Server::SystemServerTCPMessagesMiddleware(const abra::server::ClientTCPMessage &message) {
  if (serverHandlers_.find(message.messageType) == serverHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (server middleware catch)", "🔧");
  (this->*(serverHandlers_[message.messageType]))(message);

  return false;
}

bool Server::SystemClientTCPMessagesMiddleware(const abra::tools::MessageProps &message,
                                               std::uint64_t lobbyId) {
  if (clientHandlers_.find(message.messageType) == clientHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (client middleware catch)", "🔧");
  (this->*(clientHandlers_[message.messageType]))(message, lobbyId);

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

  payload::JoinLobbyInfos joinInfos{};
  snprintf(joinInfos.ip, sizeof(joinInfos.ip), "%s", this->lobbies_[id].ip);
  joinInfos.port = this->lobbies_[id].port;

  this->SendPayloadTCP(MessageServerType::kServerJoinLobbyInfos, joinInfos, message.clientId);
  logger_.Info(
      "Send lobby [" + std::to_string(id) + "] infos to client " + std::to_string(message.clientId),
      "🛃");
}

void Server::HandleLobbyAddPlayer(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::JoinLobbyInfos>(message.bitset);
  auto port = packet->GetPayload().port;
  auto ip = this->serverTCP_.GetRemoteAddress(message.clientId);

  this->clients_[message.clientId].inLobby = true;
  this->clients_[message.clientId].endpoint =
      boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);

  auto lobbyId = this->clients_[message.clientId].lobbyId;
  payload::UserJoinLobby userJoinPayload = {
      .userId = static_cast<unsigned int>(message.clientId),
  };
  snprintf(userJoinPayload.ip, sizeof(userJoinPayload.ip), "%s", ip.c_str());
  userJoinPayload.port = port;

  SendPayloadLobbyTCP(MessageServerType::kUserJoinLobby, userJoinPayload, lobbyId);

  logger_.Info("Client " + std::to_string(message.clientId) + " joined the lobby. Endpoint: " + ip +
                   ":" + std::to_string(port),
               "🛃");
}

std::queue<abra::server::ClientTCPMessage> Server::ExtractMainQueue() {
  return this->serverTCP_.ExtractQueue();
}

void Server::Join() {
  this->threadTCP_.join();
}

void Server::HandleLobbyInfos(const abra::tools::MessageProps &message, std::uint64_t lobbyId) {
  auto &lobby = this->lobbies_[lobbyId];
  auto packet = this->packetBuilder_.Build<payload::LobbyInfos>(message.data);
  auto &infos = packet->GetPayload();

  lobby.enabled = true;
  snprintf(lobby.ip, sizeof(lobby.ip), "%s", lobby.clientTCP->GetRemoteAddress().c_str());
  lobby.port = infos.port;
}
