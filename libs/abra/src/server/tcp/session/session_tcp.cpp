/*
** EPITECH PROJECT, 2024
** session_tcp.cpp
** File description:
** SessionTCP class
*/

#include "session_tcp.hpp"

#include <utility>

#include "tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost::asio;

SessionTCP::SessionTCP(boost::asio::ip::tcp::socket socket,
                       std::shared_ptr<std::queue<ClientMessage>> queue,
                       std::shared_ptr<std::mutex> mutex, std::uint64_t clientId)
    : socket_(std::move(socket)),
      buffer_(),
      queue_(std::move(queue)),
      mutex_(std::move(mutex)),
      clientId_(clientId) {}

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
  ClientMessage message = {this->clientId_, tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                           tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};

  this->mutex_->lock();
  this->queue_->push(message);
  this->mutex_->unlock();
}
