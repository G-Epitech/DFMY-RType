/*
** EPITECH PROJECT, 2024
** node.tpp
** File description:
** node class
*/

#pragma once

using namespace rtype::sdk::game::api;
using namespace abra::tools;

template<typename T>
bool Node::SendToMaster(NodeToMasterMsgType type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet to master of type " + std::to_string(type), "📦");

    auto success = this->masterSocket_.Send(packet) == SendMessageStatus::kSuccess;
    if (!success) {
      logger_.Warning("Failed to send packet to master of type " + std::to_string(type), "⚠️ ");
    }

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet to master of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}

template<typename T>
bool Node::SendToRoom(std::uint64_t socketId, NodeToRoomMsgType type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet to the room " + std::to_string(socketId) + " of type " + std::to_string(type), "📦");

    auto success = this->roomsSocket_.Send(packet, socketId) == SendMessageStatus::kSuccess;
    if (!success) {
      logger_.Warning("Failed to send packet to a room of type " + std::to_string(type), "⚠️ ");
    }

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet to a room of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}
