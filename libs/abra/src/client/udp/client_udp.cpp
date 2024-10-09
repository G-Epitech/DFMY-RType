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

std::queue<tools::MessageProps> &ClientUDP::GetQueue() {
  return queue_;
}

ClientUDP::ClientEndpoint ClientUDP::GetEndpoint() const {
  auto endpoint = socket_.local_endpoint();

  return {endpoint.address().to_string(), endpoint.port()};
}

void ClientUDP::ResolveBuffer(std::vector<char> *buffer) {
  if (buffer->size() < kPacketHeaderPropsSize / 8) {
    return;
  }

  auto bitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  std::size_t packetSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize) / 8;

  if (header.offsetFlag)
    packetSize += kPacketOffsetPropsSize / 8;
  if (header.turnFlag)
    packetSize += kPacketTurnPropsSize / 8;
  packetSize += header.payloadLength;

  if (packetSize == buffer->size()) {
    tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};
    queue_.push(message);
    return;
  }

  if (packetSize > buffer->size()) {
    return;
  }

  std::vector<char> cleanBuffer(buffer->begin(), buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(cleanBitset),
                                 tools::PacketUtils::ExportMessageIdFromBitset(cleanBitset), cleanBitset};
  queue_.push(message);

  buffer->erase(buffer->begin(), buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer);
}
