/*
** EPITECH PROJECT, 2024
** monitor.cpp
** File description:
** Monitor class
*/

#include "monitor.hpp"

using namespace rtype::sdk::game::api;

Monitor::Monitor(std::string token, const std::function<void(std::uint64_t)> &onConnect)
    : logger_("Monitor"),
      token_(std::move(token)),
      onConnect_(onConnect),
      ws_(kWebsocketPort,
          [this](const std::pair<std::uint64_t, const boost::json::object &> &message) {
            MessageHandler(message);
          }) {
  websocketThread_ = std::thread(&abra::server::ServerWebsocket::Start, &ws_);
  logger_.Info("Monitor started on port " + std::to_string(kWebsocketPort), "📟");
}

Monitor::~Monitor() = default;

void Monitor::MessageHandler(const std::pair<std::uint64_t, const boost::json::object &> &message) {
  auto &msg = message.second;
  auto type = msg.at("type").as_string().c_str();

  if (handlers_.find(type) != handlers_.end()) {
    (this->*(handlers_[type]))(message.first, msg);
  } else {
    logger_.Warning("Unknown message type: " + std::string(type), "❓");
  }
}

void Monitor::AuthHandler(std::uint64_t clientId, const boost::json::object &message) {
  auto token = message.at("token").as_string().c_str();

  if (token == token_) {
    clients_.push_back(clientId);
    logger_.Info("Client " + std::to_string(clientId) + " authenticated", "🔑");
  } else {
    logger_.Warning("Client " + std::to_string(clientId) + " failed to authenticate", "🔒");
    return;
  }

  boost::json::object response = {
      {"type", "auth"},
      {"status", "ok"},
  };
  this->ws_.SendToClient(clientId, response);
  this->onConnect_(clientId);
}

void Monitor::SendPlayersToClient(std::uint64_t clientId, const std::vector<ClientProps> &clients) {
  boost::json::array players;

  for (const auto &client : clients) {
    boost::json::object player = {
        {"id", client.id},
        {"name", client.username},
        {"inGame", client.inRoom},
    };

    players.push_back(player);
  }

  boost::json::object response = {
      {"type", "players"},
      {"players", players},
  };

  this->ws_.SendToClient(clientId, response);
}

void Monitor::SendPlayersToClients(const std::vector<ClientProps> &clients) {
  for (const auto &client : clients_) {
    SendPlayersToClient(client, clients);
  }
}
