/*
** EPITECH PROJECT, 2024
** room.tpp
** File description:
** room class
*/

#pragma once

using namespace rtype::sdk::game::api;
using namespace abra::tools;

template<typename T>
bool Room::SendToNode(RoomToNodeMsgType type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet to node of type " + std::to_string(type), "📦");

    auto success = this->nodeSocket_.Send(packet) == SendMessageStatus::kSuccess;
    if (!success) {
      logger_.Warning("Failed to send packet to node of type " + std::to_string(type), "⚠️ ");
    }

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet to node of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}

template<typename T>
bool Room::SendToClients(RoomToClientMsgType type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packets = this->packetBuilder_.Build(payload);

    logger_.Info("Send " + std::to_string(packets.size()) + " packets to " +
                 std::to_string(this->clients_.size()) + " players in lobby the lobby 📦");

    for (const auto &player: this->clients_) {
      for (const auto &packet: packets) {
        auto success = this->clientsSocket_.Send(packet, player.endpoint) == SendMessageStatus::kSuccess;
        if (!success) {
          logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");
        }
      }
    }

    return true;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet to clients of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}

template<typename T>
bool Room::SendToChats(rtype::sdk::game::api::RoomToClientMsgType type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet to clients of type " + std::to_string(type), "📦");

    for (const auto &player: this->clients_) {
      auto success = this->chatSocket_.Send(packet, player.chatId) == SendMessageStatus::kSuccess;
      if (!success) {
        logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");
      }
    }

    return true;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet to client of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}
