/*
** EPITECH PROJECT, 2024
** client.cpp
** File description:
** Client class
*/

#include "client.hpp"

using namespace rtype::sdk::game::api;
using namespace abra::client;

Client::Client(const std::string &ip, const uint32_t &port) : clientTCP_(ip, port), isConnected_(false) {
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
