/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "./master.hpp"

using namespace rtype::sdk::game::api;

Master::Master(int clientsPort, int nodesPort)
    : logger_("masterAPI"),
      clientsSocket_(
          clientsPort, [this](auto &msg) { return ClientMessageMiddleware(msg); },
          [this](auto id) { HandleClosedClientSession(id); }),
      nodesSocket_(
          nodesPort, [this](auto &msg) { return NodeMessageMiddleware(msg); },
          [this](auto id) { HandleClosedNodeSession(id); }) {
  this->InitClientsThread();
  this->InitNodesThread();
}

Master::~Master() {
  this->clientsSocket_.Close();
  this->clientsThread_.join();

  logger_.Info("Clients thread stopped", "🛑");

  this->nodesSocket_.Close();
  this->nodesThread_.join();

  logger_.Info("Nodes thread stopped", "🛑");
}

void Master::InitClientsThread() {
  this->clientsThread_ = std::thread(&abra::server::ServerTCP::Start, &this->clientsSocket_);

  logger_.Info("Clients TCP thread started", "🚀");
}

void Master::InitNodesThread() {
  this->nodesThread_ = std::thread(&abra::server::ServerTCP::Start, &this->nodesSocket_);

  logger_.Info("Nodes TCP thread started", "🚀");
}

bool Master::ClientMessageMiddleware(const abra::server::ClientTCPMessage &message) {
  if (clientMessageHandlers.find(message.messageType) == clientMessageHandlers.end()) {
    return true;
  }

  logger_.Info("Handling message (client middleware catch)", "🔧");
  (this->*(clientMessageHandlers[message.messageType]))(message);

  return false;
}

bool Master::NodeMessageMiddleware(const abra::server::ClientTCPMessage &message) {
  if (nodeMessageHandlers.find(message.messageType) == nodeMessageHandlers.end()) {
    return true;
  }

  logger_.Info("Handling message (node middleware catch)", "🔧");
  (this->*(nodeMessageHandlers[message.messageType]))(message);

  return false;
}

void Master::HandleClientConnection(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::PlayerConnect>(message.bitset);
    auto username = packet->GetPayload().username;

    SendInfos(message.clientId, true, true);

    this->AddNewClient(message.clientId, username);
  } catch (const std::exception &e) {
    logger_.Error("Error while handling client connection: " + std::string(e.what()), "❌");
  }
}

void Master::HandleRefreshInfos(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::RefreshInfos>(message.bitset);
    auto payload = packet->GetPayload();

    SendInfos(message.clientId, payload.infoGame, payload.infoRooms);
  } catch (const std::exception &e) {
    logger_.Error("Error while handling refresh infos: " + std::string(e.what()), "❌");
  }
}

void Master::AddNewClient(std::uint64_t clientId, const std::string &username) {
  Client client = {.id = clientId, .username = username, .inRoom = false};

  this->clients_.push_back(client);
  logger_.Info("New client connected: " + username, "👤");
}

std::queue<abra::server::ClientTCPMessage> Master::ExtractMainQueue() {
  return this->clientsSocket_.ExtractQueue();
}

void Master::SendGameInfos(std::uint64_t clientId) {
  payload::InfoGame infos = {
      .nbUsers = static_cast<unsigned int>(this->clients_.size()),
  };

  auto success = SendToClient(MasterToClientMsgType::kMsgTypeMTCInfoGame, infos, clientId);
  if (!success) {
    logger_.Warning("Failed to send game infos", "⚠️ ");
  }

  logger_.Info("Send game infos", "🎮");
}

void Master::SendRoomsInfos(std::uint64_t clientId) {
  bool canCreate = false;
  unsigned int nbRooms = 0;
  payload::InfoRooms infos = {};

  for (auto &node : this->nodes_) {
    if (node.second.rooms_.size() < node.second.maxRooms) {
      canCreate = true;
    }

    for (auto &room : node.second.rooms_) {
      payload::RoomStatus status = {
          .nodeId = node.first,
          .roomId = room.first,
          .nbPlayersMax = room.second.maxPlayers,
          .nbPlayers = room.second.nbPlayers,
          .difficulty = room.second.difficulty,
      };

      snprintf(status.name, sizeof(status.name), "%s", room.second.name.c_str());

      infos.rooms[nbRooms] = status;
      nbRooms++;
    }
  }

  infos.canCreate = canCreate;
  infos.nbRooms = nbRooms;

  SendToClient(MasterToClientMsgType::kMsgTypeMTCInfoRooms, infos, clientId);
}

void Master::HandleCreateRoom(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::CreateRoom>(message.bitset);
    auto payload = packet->GetPayload();

    for (auto &node : this->nodes_) {
      if (node.second.rooms_.size() >= node.second.maxRooms) {
        continue;
      }

      payload::CreateRoom room = {
          .nbPlayers = payload.nbPlayers,
          .difficulty = payload.difficulty,
      };
      snprintf(room.name, sizeof(room.name), "%s", payload.name);

      this->logger_.Info("Send creation of room", "📡");

      SendToNode(MasterToNodeMsgType::kMsgTypeMTNCreateRoom, room, node.first);
      break;
    }

    this->logger_.Info("Room creation requested", "🏠");
  } catch (const std::exception &e) {
    logger_.Error("Error while handling create room: " + std::string(e.what()), "❌");
  }
}

void Master::HandleJoinRoom(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::JoinRoom>(message.bitset);
    auto payload = packet->GetPayload();

    if (this->nodes_.find(payload.nodeId) == this->nodes_.end()) {
      this->logger_.Warning("Trying to join a room in an unknown node", "⚠️ ");
      return;
    }

    auto &node = this->nodes_[payload.nodeId];
    if (node.rooms_.find(payload.roomId) == node.rooms_.end()) {
      this->logger_.Warning("Trying to join an unknown room", "⚠️ ");
      return;
    }

    auto &room = node.rooms_[payload.roomId];
    auto &client = this->clients_[message.clientId];
    if (room.nbPlayers >= room.maxPlayers) {
      this->logger_.Warning("Trying to join a full room", "⚠️ ");
      return;
    }

    room.nbPlayers++;
    client.inRoom = true;
    client.nodeId = payload.nodeId;
    client.roomId = payload.roomId;

    SendInfoRoom(message.clientId, room, node);
    SendPlayerJoinToNode(node.id, client);

    logger_.Info("Client joined room: " + room.name, "🏠");
  } catch (const std::exception &e) {
    logger_.Error("Error while handling join room: " + std::string(e.what()), "❌");
  }
}

void Master::SendInfoRoom(std::uint64_t clientId, const Master::Room &room,
                          const Master::Node &node) {
  payload::InfoRoom infoPayload = {
      .port = room.port,
  };
  snprintf(infoPayload.ip, sizeof(infoPayload.ip), "%s",
           this->nodesSocket_.GetRemoteAddress(node.id).c_str());

  SendToClient(MasterToClientMsgType::kMsgTypeMTCInfoRoom, infoPayload, clientId);
}

void Master::SendPlayerJoinToNode(const std::uint64_t &nodeId, const Master::Client &client) {
  payload::PlayerJoinRoom joinPayload = {
      .id = client.id,
      .roomId = client.roomId,
  };
  snprintf(joinPayload.username, sizeof(joinPayload.username), "%s", client.username.c_str());
  snprintf(joinPayload.ip, sizeof(joinPayload.ip), "%s",
           this->clientsSocket_.GetRemoteAddress(client.id).c_str());

  SendToNode(MasterToNodeMsgType::kMsgTypeMTNPlayerJoinRoom, joinPayload, nodeId);
}

void Master::HandleRegisterNode(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::RegisterNode>(message.bitset);
    auto payload = packet->GetPayload();

    Node node = {
        .id = message.clientId,
        .name = payload.name,
        .maxRooms = payload.maxRooms,
    };

    this->nodes_[node.id] = std::move(node);
    logger_.Info("New node registered: " + this->nodes_[node.id].name, "🌐");
  } catch (const std::exception &e) {
    logger_.Error("Error while handling register node: " + std::string(e.what()), "❌");
  }
}

void Master::HandleRegisterRoom(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::RegisterNewRoom>(message.bitset);
    auto payload = packet->GetPayload();

    if (this->nodes_.find(message.clientId) == this->nodes_.end()) {
      this->logger_.Warning("Trying to register a room in an unknown node", "⚠️ ");
      return;
    }

    auto &node = this->nodes_[message.clientId];
    Room room = {
        .id = payload.id,
        .name = payload.name,
        .maxPlayers = payload.nbPlayers,
        .nbPlayers = 0,
        .difficulty = payload.difficulty,
        .port = payload.port,
    };

    node.rooms_[room.id] = std::move(room);
    logger_.Info("New room registered: " + std::string(node.rooms_[room.id].name), "🏠");
  } catch (const std::exception &e) {
    logger_.Error("Error while handling register room: " + std::string(e.what()), "❌");
  }
}

void Master::HandleRoomGameStarted(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::RoomGameStart>(message.bitset);
    auto payload = packet->GetPayload();

    for (auto &client : this->clients_) {
      if (client.nodeId == message.clientId && client.roomId == payload.id) {
        SendToClient(MasterToClientMsgType::kMsgTypeMTCGameStarted, '\0', client.id);
      }
    }
  } catch (const std::exception &e) {
    logger_.Error("Error while handling room game started: " + std::string(e.what()), "❌");
  }
}

void Master::HandleRoomGameEnded(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::RoomGameEnd>(message.bitset);
    auto payload = packet->GetPayload();

    payload::GameEnd end = {
        .score = payload.score,
        .time = payload.time,
        .win = payload.win,
    };

    for (auto &client : this->clients_) {
      if (client.nodeId == message.clientId && client.roomId == payload.id) {
        SendToClient(MasterToClientMsgType::kMsgTypeMTCGameEnded, end, client.id);
      }
    }

    auto &node = this->nodes_[message.clientId];
    node.rooms_.erase(payload.id);

    logger_.Info("Room game ended", "🎮");
  } catch (const std::exception &e) {
    logger_.Error("Error while handling room game ended: " + std::string(e.what()), "❌");
  }
}

void Master::SendInfos(std::uint64_t clientId, bool game, bool rooms) {
  if (game) {
    SendGameInfos(clientId);
  }

  if (rooms) {
    SendRoomsInfos(clientId);
  }
}

void Master::Join() {
  this->clientsThread_.join();
  this->nodesThread_.join();
}

void Master::HandleClosedClientSession(std::uint64_t clientId) {
  auto client = std::find_if(this->clients_.begin(), this->clients_.end(),
                             [clientId](const Client &c) { return c.id == clientId; });

  if (client == this->clients_.end()) {
    return;
  }

  this->clients_.erase(client);
  logger_.Info("Client disconnected", "👤");
}

void Master::HandleClosedNodeSession(std::uint64_t nodeId) {
  auto nodeIt = this->nodes_.find(nodeId);

  if (nodeIt == this->nodes_.end()) {
    return;
  }

  payload::GameEnd end = {
      .score = 0,
      .time = 0,
      .win = false,
  };

  for (auto &client : this->clients_) {
    if (client.nodeId == nodeId) {
      SendToClient(MasterToClientMsgType::kMsgTypeMTCGameEnded, end, client.id);
    }
  }

  this->nodes_.erase(nodeIt);
  logger_.Info("Node disconnected", "🌐");
}
