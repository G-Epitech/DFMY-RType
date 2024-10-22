/*
** EPITECH PROJECT, 2024
** server_tcp.cpp
** File description:
** ServerTCP class
*/

#include "./server_tcp.hpp"

#include <iostream>

using namespace abra::server;
using namespace boost::asio;

ServerTCP::ServerTCP(const int &port,
                     const std::function<bool(const ClientTCPMessage &)> &middleware)
    : acceptor_(ioc_, ip::tcp::endpoint(ip::tcp::v4(), port)),
      lastClientId_(0),
      middleware_(middleware),
      logger_("server_tcp") {
  mutex_ = std::make_shared<std::mutex>();
  queue_ = std::make_shared<std::queue<ClientTCPMessage>>();
}

ServerTCP::~ServerTCP() {
  this->Close();
}

void ServerTCP::Start() {
  AcceptNewConnection();

  logger_.Info("Server started on port " + std::to_string(acceptor_.local_endpoint().port()));
  ioc_.run();
}

void ServerTCP::AcceptNewConnection() {
  acceptor_.async_accept([this](boost::system::error_code error, ip::tcp::socket socket) {
    if (!error) {
      std::uint64_t clientId = lastClientId_;
      lastClientId_++;

      logger_.Info("New connection accepted");
      auto clientSession = std::make_shared<SessionTCP>(std::move(socket), this->queue_,
                                                        this->mutex_, clientId, middleware_);

      clientSession->Start();
      logger_.Info("Session started with clientID " + std::to_string(clientId));

      RegisterNewClient(clientSession, clientId);
    } else {
      logger_.Error("Error while accepting new connection: " + error.message());
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

std::queue<ClientTCPMessage> ServerTCP::ExtractQueue() {
  std::queue<ClientTCPMessage> extractedQueue;

  std::lock_guard<std::mutex> lock(*mutex_);
  extractedQueue = *queue_;

  while (!queue_->empty()) {
    queue_->pop();
  }
  return extractedQueue;
}

void ServerTCP::Close() {
  if (!acceptor_.is_open() || ioc_.stopped()) {
    return;
  }

  this->logger_.Info("Closing session");

  for (auto &client : clients_) {
    client.second->Close();
  }
  ioc_.stop();

  this->logger_.Info("Session closed");
}

std::string ServerTCP::GetRemoteAddress(std::uint64_t clientId) const {
  if (clients_.find(clientId) == clients_.end()) {
    logger_.Warning("Client not found when trying to get remote address");
    return "";
  }
  return clients_.at(clientId)->GetRemoteAddress();
}
