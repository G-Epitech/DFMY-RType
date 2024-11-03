/*
** EPITECH PROJECT, 2024
** session_tcp.cpp
** File description:
** SessionTCP class
*/

#include "./session_websocket.hpp"

#include <utility>

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::server;
using namespace boost;

SessionWebsocket::SessionWebsocket(
    boost::asio::ip::tcp::socket socket, std::uint64_t clientId,
    const std::function<void(std::pair<std::uint64_t, const boost::json::object &>)> &handler_)
    : ws_(std::move(socket)),
      buffer_(),
      clientId_(clientId),
      handler_(handler_),
      logger_("session_websocket_" + std::to_string(clientId)) {}

SessionWebsocket::~SessionWebsocket() {
  this->Close();
}

void SessionWebsocket::Start() {
  auto self(shared_from_this());

  ws_.async_accept([self](beast::error_code ec) {
    if (!ec) {
      self->ListenNewRequest();
    } else {
      return;
    }
  });
}

void SessionWebsocket::ListenNewRequest() {
  auto self(shared_from_this());

  ws_.async_read(buffer_, [self](beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (!ec) {
      auto message = beast::buffers_to_string(self->buffer_.data());
      self->HandleRequest(message);
      self->buffer_.consume(self->buffer_.size());
      self->ListenNewRequest();
    } else {
      return;
    }
  });
}

void SessionWebsocket::HandleRequest(const std::string &message) {
  logger_.Info("Received message: " + std::to_string(message.size()));

  auto json = boost::json::parse(message);
  handler_(std::make_pair(this->clientId_, json.as_object()));
}

void SessionWebsocket::Close() {
  if (!this->ws_.is_open()) {
    return;
  }

  this->logger_.Info("Closing session");
  this->ws_.close(beast::websocket::close_code::normal);
  this->logger_.Info("Session closed");
}

void SessionWebsocket::Send(const boost::json::object &message) {
  auto json = boost::json::serialize(message);
  auto self(shared_from_this());

  ws_.async_write(boost::asio::buffer(json), [self](beast::error_code ec, std::size_t) {
    if (ec) {
      self->logger_.Error("Failed to send message: " + ec.message());
    }
  });
}
