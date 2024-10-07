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

ServerTCP::ServerTCP(const int &port)
    : acceptor_(ioc_, ip::tcp::endpoint(ip::tcp::v4(), port)), lastClientId_(0) {}

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
      auto clientSession = std::make_shared<SessionTCP>(std::move(socket));

      clientSession->Start();
      RegisterNewClient(clientSession);
    } else {
      std::cerr << "ServerTCP error: " << error.message() << std::endl;
    }

    AcceptNewConnection();
  });
}

void ServerTCP::RegisterNewClient(std::shared_ptr<SessionTCP> client) {
  clients_[lastClientId_] = std::move(client);
  lastClientId_++;
}
