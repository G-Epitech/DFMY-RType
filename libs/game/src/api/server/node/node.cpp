/*
** EPITECH PROJECT, 2024
** node.cpp
** File description:
** node class
*/

#include "node.hpp"

#include <utility>

using namespace rtype::sdk::game::api;

Node::Node(std::string name, std::string token, std::size_t maxRooms, const std::string &masterIp,
           std::size_t masterPort)
    : name_(std::move(name)),
      token_(std::move(token)),
      maxRooms_(maxRooms),
      masterSocket_(masterIp, masterPort,
                    [this](auto &msg) { return MasterMessageMiddleware(msg); }),
      roomsSocket_(0, [this](auto &msg) { return RoomsMessageMiddleware(msg); }),
      logger_("nodeAPI::" + name),
      lastRoomId_(0) {}

Node::~Node() {
  this->masterSocket_.Close();
  this->masterThread_.join();
  logger_.Info("Master TCP thread stopped", "🛑");

  this->roomsSocket_.Close();
  this->roomsThread_.join();
  logger_.Info("Rooms TCP thread stopped", "🛑");
}

void Node::Start(const std::function<bool(std::uint64_t roomId, std::size_t maxPlayers,
                                          std::size_t difficulty)> &createRoomHandler) {
  InitMasterThread();
  InitRoomsThread();

  this->createRoomHandler_ = createRoomHandler;

  auto success = RegisterToMaster();
  if (success) {
    logger_.Info("Node registered to master", "🛂");
  } else {
    logger_.Error("Failed to register to master", "❌");

    exit(1);
  }
}

bool Node::RegisterToMaster() {
  payload::RegisterNode payload{};

  strncpy(payload.name, this->name_.c_str(), sizeof payload.name);
  strncpy(payload.token, this->token_.c_str(), sizeof payload.token);
  payload.maxRooms = this->maxRooms_;

  return SendToMaster(NodeToMasterMsgType::kMsgTypeNTMRegisterNode, payload);
}

void Node::RegisterNewRoom(uint64_t socketId, const payload::RegisterRoom &registerPayload) {
  auto &room = FindRoomById(registerPayload.id);
  room.socketId = socketId;

  payload::RegisterNewRoom payload{
      .id = room.id,
      .nbPlayers = room.maxPlayers,
      .difficulty = room.difficulty,
      .port = registerPayload.port,
  };

  auto success = SendToMaster(NodeToMasterMsgType::kMsgTypeNTMRegisterNewRoom, payload);
  if (success) {
    logger_.Info("Register new room [" + std::to_string(room.id) + "]", "🛃");
  }
}

void Node::InitMasterThread() {
  this->masterThread_ = std::thread(&abra::client::ClientTCP::Listen, &this->masterSocket_);

  logger_.Info("Master TCP thread started", "🚀");
}

void Node::InitRoomsThread() {
  this->roomsThread_ = std::thread(&abra::server::ServerTCP::Start, &this->roomsSocket_);

  logger_.Info("Rooms TCP thread started", "🚀");
}

bool Node::MasterMessageMiddleware(const abra::tools::MessageProps &message) {
  if (masterMessageHandlers_.find(message.messageType) == masterMessageHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (master middleware catch)", "🔧");
  (this->*(masterMessageHandlers_[message.messageType]))(message);

  return false;
}

bool Node::RoomsMessageMiddleware(const abra::server::ClientTCPMessage &message) {
  if (roomMessageHandlers_.find(message.messageType) == roomMessageHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (rooms middleware catch)", "🔧");
  (this->*(roomMessageHandlers_[message.messageType]))(message);

  return false;
}

void Node::HandleRoomCreation(const abra::tools::MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::CreateRoom>(message.data);
  auto &payload = packet->GetPayload();

  if (this->rooms_.size() >= this->maxRooms_) {
    this->logger_.Warning("Failed to create a new room (max rooms reached)", "⚠️");
    return;
  }

  RoomProps newRoom = {
      .id = lastRoomId_,
      .socketId = 0,
      .name = payload.name,
      .maxPlayers = payload.nbPlayers,
      .nbPlayers = 0,
      .difficulty = payload.difficulty,
  };

  this->createRoomHandler_(newRoom.id, newRoom.maxPlayers, newRoom.difficulty);
  this->rooms_.push_back(std::move(newRoom));

  lastRoomId_++;

  this->logger_.Info("Handle the creation of a new room", "🏠");
}

void Node::HandlePlayerJoin(const abra::tools::MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::PlayerJoin>(message.data);
  auto &payload = packet->GetPayload();
  uint64_t socketId = 0;

  try {
    auto &room = FindRoomById(payload.id);

    room.nbPlayers++;
    socketId = room.socketId;
  } catch (std::out_of_range &) {
    this->logger_.Info("Room not found", "❌");
    return;
  }

  auto success = SendToRoom(socketId, NodeToRoomMsgType::kMsgTypeNTRPlayerJoin, payload);
  if (success) {
    this->logger_.Info("Handle a new player join a room", "👥");
  }
}

void Node::HandleRoomRegister(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::RegisterRoom>(message.bitset);
  auto &payload = packet->GetPayload();

  try {
    RegisterNewRoom(message.clientId, payload);
  } catch (std::out_of_range &) {
    this->logger_.Info("Room not found", "❌");
    return;
  }
}

void Node::HandleGameStarted(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<char>(message.bitset);

  auto &room = FindRoomBySocketId(message.clientId);
  payload::RoomGameStart payload{
      .id = room.id,
  };

  SendToMaster(NodeToMasterMsgType::kMsgTypeNTMRoomGameStarted, payload);

  logger_.Info("Handle a game started", "🎮");
}

void Node::HandleGameEnded(const abra::server::ClientTCPMessage &message) {
  auto packet = this->packetBuilder_.Build<payload::GameEnd>(message.bitset);
  auto &endPayload = packet->GetPayload();

  try {
    auto &room = FindRoomBySocketId(message.clientId);

    EndGame(endPayload, room);
  } catch (std::out_of_range &) {
    this->logger_.Info("Room not found", "❌");
    return;
  }
}

void Node::EndGame(const payload::GameEnd &endPayload,
                   const rtype::sdk::game::api::Node::RoomProps &room) {
  payload::RoomGameEnd payload{
      .id = room.id,
      .score = endPayload.score,
      .time = endPayload.time,
      .win = endPayload.win,
  };

  SendToMaster(NodeToMasterMsgType::kMsgTypeNTMRoomGameEnded, payload);
  RemoveRoom(room.id);

  logger_.Info("End of the game", "🏁");
}

Node::RoomProps &Node::FindRoomById(std::uint64_t id) {
  for (auto &room : this->rooms_) {
    if (room.id == id) {
      return room;
    }
  }

  throw std::runtime_error("Room not found");
}

Node::RoomProps &Node::FindRoomBySocketId(std::uint64_t id) {
  for (auto &room : this->rooms_) {
    if (room.socketId == id) {
      return room;
    }
  }

  throw std::runtime_error("Room not found");
}

void Node::RemoveRoom(std::uint64_t id) {
  this->rooms_.erase(std::remove_if(this->rooms_.begin(), this->rooms_.end(),
                                    [id](const auto &r) { return r.id == id; }),
                     this->rooms_.end());
}