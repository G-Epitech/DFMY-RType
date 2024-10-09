/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "server.hpp"

using namespace rtype::sdk::game::api;

Server::Server(int port)
    : serverTCP_(port, [this](const ClientTCPMessage &message) {
        return SystemTCPMessagesMiddleware(message);
      }) {
  this->InitTCP();
}

void Server::InitTCP() {
  this->threadTCP_ = std::thread(&Server::ListenTCP, this);
}

void Server::ListenTCP() {
  this->serverTCP_.Start();
}

bool Server::SystemTCPMessagesMiddleware(const ClientTCPMessage &message) {
  if (this->handlers_.find(message.messageType) == this->handlers_.end()) {
    return true;
  }

  (this->*(this->handlers_[message.messageType]))(message);

  return false;
}

void Server::HandleClientConnection(const ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::Connection>(message.bitset);
  auto pseudo = packet->GetPayload().pseudo;

  payload::ConnectionInfos connectionInfos = {.onlinePlayers = 1};

  this->SendPayloadTCP(MessageServerType::kConnectionInfos, connectionInfos, message.clientId);
}
