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

ClientUDP::ClientUDP(const std::string &ip, const uint32_t &port) : socket_(ioc_) {
  ip::udp::resolver resolver(ioc_);
  ip::udp::resolver::query resolverQuery(ip::udp::v4(), ip, std::to_string(port));
  ip::udp::resolver::iterator iter = resolver.resolve(resolverQuery);
  this->receiverEndpoint_ = *iter;

  this->socket_.open(ip::udp::v4());
}

ClientUDP::~ClientUDP() {
  socket_.close();
}

void ClientUDP::listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxSize);
    ip::udp::endpoint senderEndpoint;

    std::size_t len = socket_.receive_from(buffer(buf), senderEndpoint);

    auto bitset = std::make_shared<tools::dynamic_bitset>(len * 8);
    for (std::size_t i = 0; i < len; i++) {
      bitset->Append(buf[i], 8, i * 8);
    }

    ServerMessage message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                             tools::PacketUtils::ExportMessageTypeFromBitset(bitset), bitset};
    queue_.push(message);
  }
}
