/*
** EPITECH PROJECT, 2024
** client_udp.cpp
** File description:
** ClientUDP class
*/

#include "client_udp.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::client;
using namespace boost::asio;

ClientUDP::ClientUDP(const std::string &ip, const uint32_t &port)
    : AbstractClient("client_udp"), socket_(ioc_) {
  ip::udp::resolver resolver(ioc_);
  ip::udp::resolver::query resolverQuery(ip::udp::v4(), ip, std::to_string(port));
  ip::udp::resolver::iterator iter = resolver.resolve(resolverQuery);
  this->receiverEndpoint_ = *iter;

  this->socket_.open(ip::udp::v4());
  ip::udp::endpoint localEndpoint(ip::udp::v4(), 0);
  this->socket_.bind(localEndpoint);
  uint16_t localPort = this->socket_.local_endpoint().port();

  this->logger_.Info("Client UDP started on port " + std::to_string(localPort));
}

ClientUDP::~ClientUDP() {
  this->Close();
}

void ClientUDP::Listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxBytesSize);
    ip::udp::endpoint senderEndpoint;
    std::size_t len = 0;

    try {
      len = socket_.receive_from(buffer(buf), senderEndpoint);
      logger_.Info("Received " + std::to_string(len) + " bytes", "⬅️ ");
    } catch (const std::exception &e) {
      this->logger_.Warning("Error during read: " + std::string(e.what()));
      break;
    }

    this->ResolveBuffer(&buf, len);
  }
}

std::queue<tools::MessageProps> &ClientUDP::GetQueue() {
  return queue_;
}

ClientUDP::ClientEndpoint ClientUDP::GetEndpoint() const {
  auto endpoint = socket_.local_endpoint();

  return {endpoint.address().to_string(), endpoint.port()};
}

void ClientUDP::Close() {
  if (!this->socket_.is_open() || ioc_.stopped()) {
    return;
  }

  this->logger_.Info("Closing session");

  try {
    this->socket_.shutdown(ip::udp::socket::shutdown_both);
  } catch (const std::exception &e) {
    this->logger_.Warning("Error during shutdown: " + std::string(e.what()));
  }
  this->socket_.close();

  ioc_.stop();

  this->logger_.Info("Session closed");
}
