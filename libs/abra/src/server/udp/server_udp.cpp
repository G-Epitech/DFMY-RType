/*
** EPITECH PROJECT, 2024
** server_udp.cpp
** File description:
** ServerUDP class
*/

#include "./server_udp.hpp"

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost::asio;

ServerUDP::ServerUDP()
    : socket_(ios_), buffer_(), logger_("server_udp") {
  this->socket_.open(ip::udp::v4());
  ip::udp::endpoint localEndpoint(ip::udp::v4(), 0);
  this->socket_.bind(localEndpoint);
}

ServerUDP::~ServerUDP() {
  this->Close();
}

void ServerUDP::Start() {
  ListenNewRequest();

  logger_.Info("Server started on port " + std::to_string(socket_.local_endpoint().port()));
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
  logger_.Info("Received " + std::to_string(size) + " bytes", "⬅️ ");

  ResolveBuffer(&buffer, size);
}

void ServerUDP::ResolveBuffer(std::vector<char> *buffer, std::size_t len) {
  if (buffer->size() < kPacketHeaderPropsSize / 8) {
    return;
  }

  auto bitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  std::size_t packetSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize) / 8;

  if (header.offsetFlag) {
    packetSize += kPacketOffsetPropsSize / 8;
  }
  if (header.turnFlag) {
    packetSize += kPacketTurnPropsSize / 8;
  }
  packetSize += header.payloadLength;

  if (packetSize == len) {
    return StoreMessage(bitset);
  }

  logger_.Info("Receive too bigger packet (" + std::to_string(len) + " bytes) than expected (" +
               std::to_string(packetSize) + " bytes)");

  if (packetSize > len) {
    return;
  }

  std::vector<char> cleanBuffer(
      buffer->begin(),
      buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(*buffer);

  StoreMessage(cleanBitset);

  buffer->erase(buffer->begin(),
                buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer, len - packetSize);
}

void ServerUDP::StoreMessage(std::shared_ptr<tools::dynamic_bitset> bitset) {
  ClientUDPMessage message = {this->remoteEndpoint_,
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

std::queue<ClientUDPMessage> &ServerUDP::GetQueue() {
  return this->queue_;
}

ServerUDP::ServerEndpoint ServerUDP::GetEndpoint() const {
  auto endpoint = socket_.local_endpoint();

  return {endpoint.address().to_string(), endpoint.port()};
}

std::queue<ClientUDPMessage> ServerUDP::ExtractQueue() {
  std::queue<ClientUDPMessage> extractedQueue;

  std::lock_guard<std::mutex> lock(mutex_);
  extractedQueue = queue_;

  queue_ = std::queue<ClientUDPMessage>();
  return extractedQueue;
}

void ServerUDP::Close() {
  if (!this->socket_.is_open()) {
    return;
  }

  this->logger_.Info("Closing session");

  try {
    this->socket_.shutdown(ip::udp::socket::shutdown_both);
  } catch (const std::exception &e) {
    this->logger_.Warning("Error during shutdown: " + std::string(e.what()));
  }
  this->socket_.close();

  this->logger_.Info("Session closed");
}
