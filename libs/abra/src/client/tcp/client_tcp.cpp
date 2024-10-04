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
  socket_.close();
  ios_.stop();
}

void ClientTCP::Listen() {
  while (socket_.is_open()) {
    std::vector<char> buf(kPacketMaxSize);
    boost::system::error_code error;

    std::size_t len = socket_.read_some(buffer(buf), error);
    if (error == error::eof) {
      break;
    } else if (error) {
      throw boost::system::system_error(error);
    }

    auto bitset = std::make_shared<tools::dynamic_bitset>(len * 8);
    for (std::size_t i = 0; i < len; i++) {
      bitset->Append(buf[i], 8, i * 8);
    }

    ServerMessage message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                             tools::PacketUtils::ExportMessageTypeFromBitset(bitset), bitset};
    queue_.push(message);
  }
}
