/*
** EPITECH PROJECT, 2024
** session_tcp.cpp
** File description:
** SessionTCP class
*/

#include "./session_tcp.hpp"

#include <utility>

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost::asio;

SessionTCP::SessionTCP(boost::asio::ip::tcp::socket socket,
                       std::shared_ptr<std::queue<ClientTCPMessage>> queue,
                       std::shared_ptr<std::mutex> mutex, std::uint64_t clientId,
                       const std::function<bool(const ClientTCPMessage &)> &middleware,
                       const std::function<void(std::uint64_t)> &closedSessionHandler)
    : socket_(std::move(socket)),
      buffer_(),
      queue_(std::move(queue)),
      mutex_(std::move(mutex)),
      clientId_(clientId),
      middleware_(middleware),
      closedSessionHandler_(closedSessionHandler),
      logger_("session_tcp_" + std::to_string(clientId)) {}

SessionTCP::~SessionTCP() {
  this->Close();
}

void SessionTCP::Start() {
  ListenNewRequest();
}

void SessionTCP::ListenNewRequest() {
  auto self(shared_from_this());

  try {
    socket_.async_read_some(boost::asio::buffer(buffer_),
                            [this, self](const boost::system::error_code &err, std::size_t size) {
                              if (err) {
                                if (err == boost::asio::error::eof) {
                                  logger_.Info("Connection closed by peer");
                                } else {
                                  logger_.Error("Error while reading data: " + err.message());
                                }

                                if (this->closedSessionHandler_ != nullptr) {
                                  this->closedSessionHandler_(this->clientId_);
                                }
                                return;
                              }
                              if (size > 0) {
                                logger_.Info("Received " + std::to_string(size) + " bytes", "⬅️ ");
                                HandleRequest(size);
                              } else {
                                logger_.Warning("Receive empty data");
                              }
                              ListenNewRequest();
                            });
  } catch (const std::exception &e) {
    logger_.Warning("Session closed: " + std::string(e.what()));
  }
}

void SessionTCP::HandleRequest(const std::size_t &size) {
  std::vector<char> buffer = std::vector<char>(buffer_.begin(), buffer_.begin() + size);

  auto bitset = std::make_shared<tools::dynamic_bitset>(buffer, size);
  ClientTCPMessage message = {this->clientId_,
                              tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                              tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};

  auto save = this->middleware_(message);
  if (save) {
    std::unique_lock<std::mutex> lock(*this->mutex_);

    this->queue_->push(message);

    logger_.Info("New message saved in queue. Type: " + std::to_string(message.messageType));
  } else {
    logger_.Info("New message handled by middleware. Type: " + std::to_string(message.messageType));
  }
}

void SessionTCP::Close() {
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

std::string SessionTCP::GetRemoteAddress() const {
  return this->socket_.remote_endpoint().address().to_string();
}
