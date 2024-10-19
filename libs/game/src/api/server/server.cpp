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
}

std::uint64_t Server::CreateLobby(const std::string &name) {
  std::uint64_t lobbyId = this->lobbies_.size();

  this->lobbies_[lobbyId] = Lobby({.id = lobbyId, .name = name});

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

  payload::JoinLobbyInfos joinInfos{};
  // TODO: Add lobby infos

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
