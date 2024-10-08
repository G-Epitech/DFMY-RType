/*
** EPITECH PROJECT, 2024
** client.cpp
** File description:
** Client class
*/

#include "client.hpp"

using namespace rtype::sdk::game::api;
using namespace abra::client;
using namespace abra::tools;

Client::Client(const std::string &ip, const uint32_t &port)
    : clientTCP_(ip, port), isConnected_(false) {
  InitTCP();
}

Client::~Client() {
  this->threadTCP_.join();
  this->threadUDP_.join();
};

void Client::InitTCP() {
  this->threadTCP_ = std::thread(&Client::ListenTCP, this);
}

void Client::ListenTCP() {
  this->clientTCP_.Listen();
}

bool Client::IsConnected() const {
  return this->isConnected_;
}

bool Client::connect(const payload::Connection &payload) {
  this->packetBuilder_.SetMessageType(MessageClientType::kConnection)
      .SetPayloadType(PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build<payload::Connection>(payload);

  auto success = this->clientTCP_.Send(packet) == SendMessageStatus::kSuccess;
  this->isConnected_ = success;

  return success;
}
