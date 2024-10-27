/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "./master.hpp"

using namespace rtype::sdk::game::api;

Master::Master(int port)
    : logger_("serverAPI"),
      clientsSocket_(port, [this](auto &msg) { return ClientMessageMiddleware(msg); }),
      nodesSocket_(port, [this](auto &msg) { return NodeMessageMiddleware(msg); }) {
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
  auto packet = this->packetBuilder_.Build<payload::PlayerConnect>(message.bitset);
  auto username = packet->GetPayload().username;

  SendInfos(true, true, message.clientId);

  this->AddNewClient(message.clientId, username);
}

void Master::HandleRefreshInfos(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::RefreshInfos>(message.bitset);
  auto payload = packet->GetPayload();

  SendInfos(payload.infoGame, payload.infoRooms, message.clientId);
}

void Master::AddNewClient(std::uint64_t clientId, const std::string &username) {
  Client client = {.id = clientId, .username = username, .inLobby = false};

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

  SendToClient(MasterToClientMsgType::kMsgTypeMTCInfoGame, infos, clientId);
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

      strcpy(status.name, room.second.name.c_str());

      infos.rooms[nbRooms] = status;
      nbRooms++;
    }
  }

  infos.canCreate = canCreate;
  infos.nbRooms = nbRooms;

  SendToClient(MasterToClientMsgType::kMsgTypeMTCInfoRooms, infos, clientId);
}

void Master::HandleCreateRoom(const abra::server::ClientTCPMessage &message) {
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
    strcpy(room.name, payload.name);

    SendToNode(MasterToNodeMsgType::kMsgTypeMTNCreateRoom, room, node.first);
    break;
  }
}

void Master::HandleJoinRoom(const abra::server::ClientTCPMessage &message) {
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
  client.inLobby = true;
  client.nodeId = payload.nodeId;
  client.roomId = payload.roomId;

  SendToNode(MasterToNodeMsgType::kMsgTypeMTNCreateRoom, payload, payload.nodeId);
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
