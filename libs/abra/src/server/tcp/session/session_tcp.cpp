/*
** EPITECH PROJECT, 2024
** session_tcp.cpp
** File description:
** SessionTCP class
*/

#include "session_tcp.hpp"

#include "tools/packet/packet_utils.hpp"
#include "tools/packet/props/props.hpp"

using namespace abra::server;
using namespace boost::asio;

SessionTCP::SessionTCP(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)), buffer_(kPacketMaxBytesSize) {}

SessionTCP::~SessionTCP() {
  socket_.close();
}

void SessionTCP::Start() {
  ListenNewRequest();
}

void SessionTCP::ListenNewRequest() {
  auto self(shared_from_this());

  buffer_.clear();
  socket_.async_read_some(
      buffer(buffer_), [this, self](boost::system::error_code error, std::size_t len) {
        if (!error) {
          auto bitset = std::make_shared<tools::dynamic_bitset>(buffer_);
          tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                         tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                         bitset};
          queue_.push(message);
        }
      });
}
