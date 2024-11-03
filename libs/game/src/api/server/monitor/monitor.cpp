/*
** EPITECH PROJECT, 2024
** monitor.cpp
** File description:
** Monitor class
*/

#include "monitor.hpp"

using namespace rtype::sdk::game::api;

Monitor::Monitor()
    : logger_("Monitor"),
      ws_(kWebsocketPort,
          [this](const std::pair<std::uint64_t, const boost::json::object &> &message) {
            MessageHandler(message);
          }) {
  websocketThread_ = std::thread(&abra::server::ServerWebsocket::Start, &ws_);
  logger_.Info("Monitor started on port " + std::to_string(kWebsocketPort), "📟");
}

Monitor::~Monitor() = default;

void Monitor::MessageHandler(const std::pair<std::uint64_t, const boost::json::object &> &message) {
  auto msg = message.second;
  auto type = msg.at("type").as_string();

  std::cout << "Message received: " << type << std::endl;
}
