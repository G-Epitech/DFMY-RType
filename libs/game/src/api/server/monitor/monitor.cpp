/*
** EPITECH PROJECT, 2024
** monitor.cpp
** File description:
** Monitor class
*/

#include "monitor.hpp"

using namespace rtype::sdk::game::api;

Monitor::Monitor(std::string token, const std::function<void(std::uint64_t)> &onConnect,
                 const std::function<void(const std::string &, std::uint64_t)> &onEvent)
    : logger_("Monitor"),
      token_(std::move(token)),
      onConnect_(onConnect),
      onEvent_(onEvent),
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

void Monitor::SendNodesToClient(std::uint64_t clientId,
                                const std::map<std::uint64_t, NodeProps> &nodes) {
  boost::json::array nodesArray;

  for (const auto &node : nodes) {
    auto status = "partial";
    if (node.second.maxRooms <= node.second.rooms_.size())
      status = "unavailable";
    if (node.second.rooms_.empty())
      status = "free";

    boost::json::object nodeObject = {{"id", node.second.id},
                                      {"name", node.second.name},
                                      {"maxRooms", node.second.maxRooms},
                                      {"currentRooms", node.second.rooms_.size()},
                                      {"status", status}};

    nodesArray.push_back(nodeObject);
  }

  boost::json::object response = {
      {"type", "nodes"},
      {"nodes", nodesArray},
  };

  this->ws_.SendToClient(clientId, response);

  std::vector<RoomProps> rooms;
  for (const auto &node : nodes) {
    for (const auto &room : node.second.rooms_) {
      rooms.push_back(room.second);
    }
  }

  SendRoomsToClient(clientId, rooms);
}

void Monitor::SendNodesToClients(const std::map<std::uint64_t, NodeProps> &nodes) {
  for (const auto &client : clients_) {
    SendNodesToClient(client, nodes);
  }
}

void Monitor::SendRoomsToClient(std::uint64_t clientId, const std::vector<RoomProps> &rooms) {
  boost::json::array roomsArray;

  for (const auto &room : rooms) {
    boost::json::object roomObject = {
        {"id", room.id},
        {"name", room.name},
        {"players", room.nbPlayers},
        {"maxPlayers", room.maxPlayers},
    };

    roomsArray.push_back(roomObject);
  }

  boost::json::object response = {
      {"type", "rooms"},
      {"rooms", roomsArray},
  };

  std::cout << response << std::endl;
  this->ws_.SendToClient(clientId, response);
}

void Monitor::SendRoomsToClients(const std::vector<RoomProps> &rooms) {
  for (const auto &client : clients_) {
    SendRoomsToClient(client, rooms);
  }
}

void Monitor::KickHandler(std::uint64_t clientId, const boost::json::object &message) {
  auto token = message.at("token").as_string().c_str();
  if (token != token_) {
    logger_.Warning("Client " + std::to_string(clientId) + " try to kick without perms", "🔒");
    return;
  }

  this->onEvent_("kick", message.at("id").as_int64());
  logger_.Info("Client " + std::to_string(clientId) + " kicked " +
                   std::to_string(message.at("id").as_int64()),
               "👢");
}
