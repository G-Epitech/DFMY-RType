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

    auto bitset = std::make_shared<tools::dynamic_bitset>(buf);
    tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};
    queue_.push(message);
  }
}

const std::queue<tools::MessageProps> &ClientTCP::GetQueue() {
  return queue_;
}
