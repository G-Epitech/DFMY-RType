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
  ioc_.stop();
}

void ClientUDP::Listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxBytesSize);
    ip::udp::endpoint senderEndpoint;

    std::size_t len = socket_.receive_from(buffer(buf), senderEndpoint);

    auto bitset = std::make_shared<tools::dynamic_bitset>(buf);
    tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};
    queue_.push(message);
  }
}
