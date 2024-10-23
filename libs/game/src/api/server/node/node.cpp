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
      masterSocket_(masterIp, masterPort, nullptr),
      roomsSocket_(0, nullptr),
      logger_("nodeAPI::" + name){}

Node::~Node() {
  this->masterSocket_.Close();
  this->masterThread_.join();
  logger_.Info("Master TCP thread stopped", "🛑");

  this->roomsSocket_.Close();
  this->roomsThread_.join();
  logger_.Info("Rooms TCP thread stopped", "🛑");
}

void Node::Start() {
  InitMasterThread();
  InitRoomsThread();

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
