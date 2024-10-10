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

void Server::InitTCP() {
  this->threadTCP_ = std::thread(&Server::ListenTCP, this);
  logger_.Info("Server TCP thread started", "🚀");
}

void Server::ListenTCP() {
  this->serverTCP_.Start();
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

  logger_.Info("New client connected: " + std::string(pseudo), "👤");

  payload::ConnectionInfos connectionInfos = {.onlinePlayers = 1};

  this->SendPayloadTCP(MessageServerType::kConnectionInfos, connectionInfos, message.clientId);
}
