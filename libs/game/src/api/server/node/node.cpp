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
      roomsSocket_(0, nullptr),
      logger_("nodeAPI::" + name) {}

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

void Node::HandleRoomCreation(const abra::tools::MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::CreateRoom>(message.data);
  auto &payload = packet->GetPayload();

  if (this->rooms_.size() >= this->maxRooms_) {
    this->logger_.Warning("Failed to create a new room (max rooms reached)", "⚠️");
    return;
  }

  RoomProps newRoom = {
      .id = this->rooms_.size(),
      .socketId = 0,
      .name = payload.name,
      .maxPlayers = payload.nbPlayers,
      .nbPlayers = 0,
      .difficulty = payload.difficulty,
  };

  this->createRoomHandler_(newRoom.id, newRoom.maxPlayers, newRoom.difficulty);
  this->rooms_.push_back(std::move(newRoom));

  this->logger_.Info("Handle the creation of a new room", "🏠");
}
