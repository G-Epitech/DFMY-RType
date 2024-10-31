/*
** EPITECH PROJECT, 2024
** server.tpp
** File description:
** server class
*/

#pragma once

using namespace rtype::sdk::game::api;
using namespace abra::tools;

template<typename T>
bool Master::SendToClient(const MasterToClientMsgType &type, const T &payload, const std::uint64_t &clientId) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send TCP packet of type " + std::to_string(type), "📦");

    auto success = this->clientsSocket_.Send(packet, clientId) == SendMessageStatus::kSuccess;
    if (!success)
      logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}

template<typename T>
bool Master::SendToNode(const rtype::sdk::game::api::MasterToNodeMsgType &type, const T &payload, const std::uint64_t &nodeId) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send TCP packet of type " + std::to_string(type), "📦");

    auto success = this->nodesSocket_.Send(packet, nodeId) == SendMessageStatus::kSuccess;
    if (!success)
      logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet of type " + std::to_string(type) + " : " + e.what(), "❌");
    return false;
  }
}
