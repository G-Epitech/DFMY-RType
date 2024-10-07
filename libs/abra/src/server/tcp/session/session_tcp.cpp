/*
** EPITECH PROJECT, 2024
** session_tcp.cpp
** File description:
** SessionTCP class
*/

#include "session_tcp.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost::asio;

SessionTCP::SessionTCP(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)), buffer_() {}

SessionTCP::~SessionTCP() {
  socket_.close();
}

void SessionTCP::Start() {
  ListenNewRequest();
}

void SessionTCP::ListenNewRequest() {
  auto self(shared_from_this());

  socket_.async_read_some(boost::asio::buffer(buffer_),
                          [this, self](const boost::system::error_code &err, std::size_t size) {
                            if (err)
                              return;
                            if (size > 0) {
                              HandleRequest(size);
                            }
                            ListenNewRequest();
                          });
}

void SessionTCP::HandleRequest(const std::size_t &size) {
  std::vector<char> buffer = std::vector<char>(buffer_.begin(), buffer_.begin() + size);

  auto bitset = std::make_shared<tools::dynamic_bitset>(buffer);
  tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                 tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};

  queue_.push(message);
}
