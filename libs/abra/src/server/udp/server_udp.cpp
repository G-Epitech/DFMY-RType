/*
** EPITECH PROJECT, 2024
** server_udp.cpp
** File description:
** ServerUDP class
*/

#include "server_udp.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost::asio;

ServerUDP::ServerUDP(const int &port)
    : socket_(ios_, ip::udp::endpoint(ip::udp::v4(), port)), buffer_() {}

ServerUDP::~ServerUDP() {
  this->ios_.stop();
}

void ServerUDP::Start() {
  ListenNewRequest();
  this->ios_.run();
}

void ServerUDP::ListenNewRequest() {
  this->socket_.async_receive_from(buffer(this->buffer_), this->remoteEndpoint_,
                                   [this](const boost::system::error_code &err, std::size_t size) {
                                     if (err)
                                       return;
                                     if (size > 0) {
                                       HandleRequest(size);
                                     }
                                     ListenNewRequest();
                                   });
}

void ServerUDP::HandleRequest(const std::size_t &size) {
  std::vector<char> buffer = std::vector<char>(buffer_.begin(), buffer_.begin() + size);

  auto bitset = std::make_shared<tools::dynamic_bitset>(buffer);

  ClientMessage message = {this->remoteEndpoint_,
                           tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                           tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};

  this->mutex_.lock();
  queue_.push(message);
  this->mutex_.unlock();
}

void ServerUDP::LockQueue() {
  this->mutex_.lock();
}

void ServerUDP::UnlockQueue() {
  this->mutex_.unlock();
}

std::queue<ClientMessage> &ServerUDP::GetQueue() {
  return this->queue_;
}
