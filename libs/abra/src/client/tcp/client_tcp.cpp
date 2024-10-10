/*
** EPITECH PROJECT, 2024
** client_tcp.cpp
** File description:
** ClientTCP class
*/

#include "client_tcp.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::client;
using namespace boost::asio;

ClientTCP::ClientTCP(const std::string &ip, const std::uint32_t &port)
    : socket_(ios_), logger_("client_tcp") {
  ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);

  socket_.connect(endpoint);
  logger_.Info("Connected to " + ip + ":" + std::to_string(port));
}

ClientTCP::~ClientTCP() {
  this->socket_.shutdown(ip::tcp::socket::shutdown_both);
  this->socket_.close();
}

void ClientTCP::Listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxBytesSize);
    boost::system::error_code error;

    std::size_t len = socket_.read_some(buffer(buf), error);
    logger_.Info("Received " + std::to_string(len) + " bytes", "⬅️");

    if (error == error::eof) {
      logger_.Info("Connection closed cleanly by peer");
      break;
    } else if (error) {
      throw boost::system::system_error(error);
    }

    ResolveBuffer(&buf);
  }
}

std::queue<tools::MessageProps> &ClientTCP::GetQueue() {
  return queue_;
}
