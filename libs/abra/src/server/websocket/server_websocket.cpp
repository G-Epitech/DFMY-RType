/*
** EPITECH PROJECT, 2024
** server_tcp.cpp
** File description:
** ServerTCP class
*/

#include "./server_websocket.hpp"

#include <iostream>

using namespace abra::server;
using namespace boost::asio;

ServerWebsocket::ServerWebsocket(
    const int &port,
    const std::function<void(std::pair<std::uint64_t, const boost::json::object &>)> &handler)
    : acceptor_(ioc_, ip::tcp::endpoint(ip::tcp::v4(), port)),
      lastClientId_(0),
      handler_(handler),
      logger_("websocket") {}

ServerWebsocket::~ServerWebsocket() {
  this->Close();
}

void ServerWebsocket::Start() {
  AcceptNewConnection();

  logger_.Info("Websocket started on port " + std::to_string(acceptor_.local_endpoint().port()));
  ioc_.run();
}

void ServerWebsocket::AcceptNewConnection() {
  acceptor_.async_accept([this](boost::system::error_code error, ip::tcp::socket socket) {
    if (!error) {
      std::uint64_t clientId = lastClientId_;
      lastClientId_++;

      logger_.Info("New connection accepted");
      auto clientSession =
          std::make_shared<SessionWebsocket>(std::move(socket), clientId, handler_);

      clientSession->Start();
      logger_.Info("Session started with clientID " + std::to_string(clientId));

      RegisterNewClient(clientSession, clientId);
    } else {
      logger_.Error("Error while accepting new connection: " + error.message());
    }

    AcceptNewConnection();
  });
}

void ServerWebsocket::RegisterNewClient(std::shared_ptr<SessionWebsocket> client,
                                        const std::uint64_t &clientId) {
  clients_[clientId] = std::move(client);
}

void ServerWebsocket::Close() {
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

void ServerWebsocket::SendToClient(const std::uint64_t &clientId,
                                   const boost::json::object &message) {
  if (clients_.find(clientId) == clients_.end() || !clients_[clientId]) {
    logger_.Error("Client not found");
    return;
  }

  clients_[clientId]->Send(message);
}
