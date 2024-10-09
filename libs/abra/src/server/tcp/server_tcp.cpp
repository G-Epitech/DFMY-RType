/*
** EPITECH PROJECT, 2024
** server_tcp.cpp
** File description:
** ServerTCP class
*/

#include "server_tcp.hpp"

#include <iostream>

using namespace abra::server;
using namespace boost::asio;

ServerTCP::ServerTCP(const int &port,
                     const std::function<bool(const ClientTCPMessage &)> &middleware)
    : acceptor_(ioc_, ip::tcp::endpoint(ip::tcp::v4(), port)),
      lastClientId_(0),
      middleware_(middleware) {}

ServerTCP::~ServerTCP() {
  ioc_.stop();
}

void ServerTCP::Start() {
  AcceptNewConnection();
  ioc_.run();
}

void ServerTCP::AcceptNewConnection() {
  acceptor_.async_accept([this](boost::system::error_code error, ip::tcp::socket socket) {
    if (!error) {
      std::uint64_t clientId = lastClientId_;
      lastClientId_++;

      auto clientSession = std::make_shared<SessionTCP>(std::move(socket), this->queue_,
                                                        this->mutex_, clientId, middleware_);

      clientSession->Start();
      RegisterNewClient(clientSession, clientId);
    } else {
      std::cerr << "ServerTCP error: " << error.message() << std::endl;
    }

    AcceptNewConnection();
  });
}

void ServerTCP::RegisterNewClient(std::shared_ptr<SessionTCP> client,
                                  const std::uint64_t &clientId) {
  clients_[clientId] = std::move(client);
}

void ServerTCP::LockQueue() {
  mutex_->lock();
}

void ServerTCP::UnlockQueue() {
  mutex_->unlock();
}

const std::shared_ptr<std::queue<ClientTCPMessage>> &ServerTCP::GetQueue() {
  return queue_;
}
