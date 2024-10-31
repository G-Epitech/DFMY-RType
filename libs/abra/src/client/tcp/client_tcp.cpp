/*
** EPITECH PROJECT, 2024
** client_tcp.cpp
** File description:
** ClientTCP class
*/

#include "./client_tcp.hpp"

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::client;
using namespace boost::asio;

ClientTCP::ClientTCP(const std::string &ip, const std::uint32_t &port,
                     const std::function<bool(const tools::MessageProps &)> &middleware)
    : AbstractClient("client_tcp"), socket_(ios_) {
  ip::tcp::endpoint endpoint(ip::address::from_string(ip.c_str()), port);

  socket_.connect(endpoint);
  logger_.Info("Connected to " + ip + ":" + std::to_string(port));

  this->middleware_ = middleware;
}

ClientTCP::~ClientTCP() {
  this->Close();
}

void ClientTCP::Listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxBytesSize);
    boost::system::error_code error;

    std::size_t len = socket_.read_some(buffer(buf), error);
    logger_.Info("Received " + std::to_string(len) + " bytes", "⬅️ ");

    if (error == error::eof) {
      logger_.Info("Connection closed cleanly by peer");
      break;
    } else if (error) {
      logger_.Warning("Error during read: " + error.message(), "⚠️ ");
      break;
    }

    ResolveBuffer(&buf, len);
  }
}

std::queue<tools::MessageProps> &ClientTCP::GetQueue() {
  return queue_;
}

void ClientTCP::Close() {
  if (!this->socket_.is_open()) {
    return;
  }

  this->logger_.Info("Closing session");

  try {
    this->socket_.shutdown(ip::udp::socket::shutdown_both);
  } catch (const std::exception &e) {
    this->logger_.Warning("Error during shutdown: " + std::string(e.what()));
  }
  this->socket_.close();

  this->logger_.Info("Session closed");
}

std::string ClientTCP::GetRemoteAddress() const {
  return socket_.remote_endpoint().address().to_string();
}
