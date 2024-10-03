/*
** EPITECH PROJECT, 2024
** client_tcp.cpp
** File description:
** ClientTCP class
*/

#include "client_tcp.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::client;

ClientTCP::ClientTCP(const std::string &ip, const std::uint32_t &port) : socket_(ios_) {
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);

  socket_.connect(endpoint);
}

ClientTCP::~ClientTCP() {
  socket_.close();
}

void ClientTCP::listen() {
  unsigned int maxPacketSize = kPacketHeaderPropsSize + kPacketMessagePropsSize +
                               kPacketOffsetPropsSize + kPacketTurnPropsSize + 1024;
  while (socket_.is_open()) {
    std::vector<char> buffer(maxPacketSize);
    boost::system::error_code error;

    std::size_t len = socket_.read_some(boost::asio::buffer(buffer), error);
    if (error == boost::asio::error::eof) {
      break;
    } else if (error) {
      throw boost::system::system_error(error);
    }

    auto bitset = std::make_shared<abra::tools::dynamic_bitset>(len * 8);
    for (std::size_t i = 0; i < len; i++) {
      bitset->Append(buffer[i], 8, i * 8);
    }

    ServerMessage message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                             tools::PacketUtils::ExportMessageTypeFromBitset(bitset), bitset};
    queue_.push(message);
  }
}
