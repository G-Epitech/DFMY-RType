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

ClientTCP::ClientTCP(const std::string &ip, const std::uint32_t &port) : socket_(ios_) {
  ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);

  socket_.connect(endpoint);
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
    if (error == error::eof) {
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

void ClientTCP::ResolveBuffer(std::vector<char> *buffer) {
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
