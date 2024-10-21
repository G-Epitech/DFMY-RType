/*
** EPITECH PROJECT, 2024
** lobby.cpp
** File description:
** Lobby class
*/

#include "lobby.hpp"

using namespace rtype::sdk::game::api;

Lobby::Lobby(int port, std::function<void(std::uint64_t)> &newPlayerHandler)
    : serverTCP_(port,
                 [this](const abra::server::ClientTCPMessage &message) {
                   return this->SystemTCPMessagesMiddleware(message);
                 }),
      serverUDP_(),
      logger_("lobbyAPI"),
      masterId_(0),
      lobbyId_(0) {
  this->InitTCP();
  this->InitUDP();

  this->newPlayerHandler_ = newPlayerHandler;
}

Lobby::~Lobby() {
  this->serverTCP_.Close();
  this->threadTCP_.join();

  logger_.Info("Server TCP thread stopped", "🛑");

  this->serverUDP_.Close();
  this->threadUDP_.join();

  logger_.Info("Server UDP thread stopped", "🛑");
}

void Lobby::InitTCP() {
  this->threadTCP_ = std::thread(&Lobby::ListenTCP, this);
  logger_.Info("Server TCP thread started", "🚀");
}

void Lobby::ListenTCP() {
  this->serverTCP_.Start();
}

void Lobby::InitUDP() {
  this->threadUDP_ = std::thread(&Lobby::ListenUDP, this);
  logger_.Info("Server UDP thread started", "🚀");
}

void Lobby::ListenUDP() {
  this->serverUDP_.Start();
}

std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> Lobby::ExtractQueue() {
  auto queue = this->serverUDP_.ExtractQueue();
  std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> extractedQueue;

  while (!queue.empty()) {
    auto message = queue.front();
    auto userId = this->FindUserByEndpoint(message.endpoint);

    extractedQueue.emplace(userId, queue.front());
    queue.pop();
  }

  return extractedQueue;
}

std::uint64_t Lobby::FindUserByEndpoint(const boost::asio::ip::udp::endpoint &endpoint) {
  for (auto &client : this->clients_) {
    if (client.endpoint.address().to_string() == endpoint.address().to_string() &&
        client.endpoint.port() == endpoint.port()) {
      return client.id;
    }
  }

  logger_.Warning("User not found by endpoint", "⚠️ ");

  return 0;
}

bool Lobby::SendPlayersState(const std::vector<payload::PlayerState> &state) {
  auto success = this->SendPayloadsUDP(MessageLobbyType::kPlayersState, state);
  if (success) {
    this->logger_.Info("Players state sent", "🦹");
  }

  return success;
}

bool Lobby::SendEnemiesState(const std::vector<payload::EnemyState> &state) {
  auto success = this->SendPayloadsUDP(MessageLobbyType::kEnemiesState, state);
  if (success) {
    this->logger_.Info("Enemies state sent", "🧌");
  }

  return success;
}

bool Lobby::SendBulletsState(const std::vector<payload::BulletState> &state) {
  auto success = this->SendPayloadsUDP(MessageLobbyType::kBulletsState, state);
  if (success) {
    this->logger_.Info("Bullets state sent", "💥");
  }

  return success;
}

bool Lobby::SystemTCPMessagesMiddleware(const abra::server::ClientTCPMessage &message) {
  if (handlers_.find(message.messageType) == handlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (middleware catch)", "🔧");
  (this->*(handlers_[message.messageType]))(message);

  return false;
}

void Lobby::HandleMasterConnection(const server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::RegisterLobby>(message.bitset);

  this->masterId_ = message.clientId;
  this->lobbyId_ = packet->GetPayload().lobbyId;

  auto port = this->serverUDP_.GetEndpoint().port;
  payload::LobbyInfos lobbyInfos = {.port = port};

  SendPayloadTCP(MessageLobbyType::kLobbyInfos, lobbyInfos);

  logger_.Info("Master connected", "👑");
}

void Lobby::HandleNewUser(const server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::UserJoinLobby>(message.bitset);
  auto ip = packet->GetPayload().ip;
  auto port = packet->GetPayload().port;

  this->clients_.push_back({.id = message.clientId,
                            .endpoint = boost::asio::ip::udp::endpoint(
                                boost::asio::ip::address::from_string(ip), port)});

  this->newPlayerHandler_(message.clientId);

  logger_.Info("New user connected: " + std::to_string(message.clientId), "👤");
}
