/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "server.hpp"

using namespace rtype::sdk::game::api;

Server::Server(int port)
    : logger_("serverAPI"), serverTCP_(port, [this](const ClientTCPMessage &message) {
        return this->SystemTCPMessagesMiddleware(message);
      }) {
  this->InitTCP();
}

void Server::CreateLobby(const std::string &name) {
  std::uint64_t lobbyId = this->lobbies_.size();
  std::uint64_t port = 30000 + lobbyId;

  this->lobbies_[lobbyId] = Lobby(
      {.id = lobbyId, .name = name, .serverUDP = std::make_unique<abra::server::ServerUDP>(port)});
  this->InitUDP(lobbyId);
  logger_.Info("Register new lobby [" + std::to_string(lobbyId) + "]", "🛃");
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

bool Server::SystemTCPMessagesMiddleware(const ClientTCPMessage &message) {
  if (handlers_.find(message.messageType) == handlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (middleware catch)", "🔧");
  (this->*(handlers_[message.messageType]))(message);

  return false;
}

void Server::HandleClientConnection(const ClientTCPMessage &message) {
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

void Server::HandleLobbyJoin(const ClientTCPMessage &message) {
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

void Server::HandleLobbyAddPlayer(const ClientTCPMessage &message) {
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

  logger_.Info("Client " + std::to_string(message.clientId) + " joined the lobby", "🛃");
}
