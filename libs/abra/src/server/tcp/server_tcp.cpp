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

ServerTCP::ServerTCP(const int &port) : acceptor_(ioc_, ip::tcp::v4(), port) {}

ServerTCP::~ServerTCP() {
  acceptor_.close();
  ioc_.stop();
}

void ServerTCP::Start() {
  AcceptNewConnection();
}

void ServerTCP::AcceptNewConnection() {
  acceptor_.async_accept([this](boost::system::error_code error, ip::tcp::socket socket) {
    if (!error) {
      // start client session
    } else {
      std::cerr << "ServerTCP error: " << error.message() << std::endl;
    }

    AcceptNewConnection();
  });
}
