/*
** EPITECH PROJECT, 2024
** lobby.cpp
** File description:
** Lobby class
*/

#include "lobby.hpp"

using namespace rtype::sdk::game::api;

Lobby::Lobby(int port) : serverTCP_(port, [this](const abra::server::ClientTCPMessage &message) {
  return this->SystemTCPMessagesMiddleware(message);
}), serverUDP_(), logger_("lobbyAPI"), masterId_(0) {
  this->InitTCP();
  this->InitUDP();
}

Lobby::~Lobby() {
  this->serverTCP_.Close();
  this->threadTCP_.join();

  logger_.Info("Server TCP thread stopped", "🛑");

  this->serverUDP_.Close();
  this->threadUDP_.join();

  logger_.Info("Server UDP thread stopped", "🛑");
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
  for (auto &client: this->clients_) {
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
  return true;
}
