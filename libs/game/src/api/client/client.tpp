/*
** EPITECH PROJECT, 2024
** client.tpp
** File description:
** client class
*/

#pragma once

namespace api = rtype::sdk::game::api;
namespace abt = abra::tools;

template <typename T>
bool api::Client::SendPayloadTCP(const ClientToMasterMsgType &type, const T &payload) {
  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet (TCP) of type " + std::to_string(type), "📦");

    auto success = this->clientTCP_.Send(packet) == abt::SendMessageStatus::kSuccess;
    if (!success)
      logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet of type " + std::to_string(type) + ": " + e.what(), "❌");
    return false;
  }
}

template <typename T>
bool api::Client::SendChatPayloadTPC(const rtype::sdk::game::api::ClientToRoomMsgType &type, const T &payload) {
  if (!this->chatTCP_.has_value()) {
    this->logger_.Error("Chat TCP is not initialized", "❌");
    return false;
  }

  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet (chat TCP) of type " + std::to_string(type), "📦");

    auto success = this->chatTCP_->Send(packet) == abt::SendMessageStatus::kSuccess;
    if (!success)
      logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet of type " + std::to_string(type) + ": " + e.what(), "❌");
    return false;
  }
}

template <typename T>
bool api::Client::SendPayloadUDP(const ClientToRoomMsgType &type, const T &payload) {
  if (!this->clientUDP_.has_value())
    return false;

  try {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
    auto packet = this->packetBuilder_.Build(payload);

    logger_.Info("Send packet (UDP) of type " + std::to_string(type), "📦");

    auto success = this->clientUDP_->Send(packet) == abt::SendMessageStatus::kSuccess;
    if (!success)
      logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

    return success;
  } catch (const std::exception &e) {
    logger_.Error("Failed to send packet of type " + std::to_string(type) + ": " + e.what(), "❌");
    return false;
  }
}

template <typename T>
std::vector<T> api::Client::ResolveUDPPayloads(RoomToClientMsgType type, const ServerMessage &message) {
  if (message.messageType != type || message.protocolType != NetworkProtocolType::kUDP) {
    return {};
  }
  auto elements = std::vector<T>();

  for (auto &data : message.data) {
    try {
      auto packet = this->packetBuilder_.Build<T>(data);
      elements.push_back(packet->GetPayload());
    } catch (const std::exception &e) {
      logger_.Error("Failed to resolve UDP payload: " + std::string(e.what()), "❌");
    }
  }

  return elements;
}


template <typename T>
std::vector<T> api::Client::ResolveTCPPayloads(MasterToClientMsgType type, const ServerMessage &message) {
  if (message.messageType != type || message.protocolType != NetworkProtocolType::kTCP) {
    return {};
  }
  auto elements = std::vector<T>();

  for (auto &data : message.data) {
    try {
      auto packet = this->packetBuilder_.Build<T>(data);
      elements.push_back(packet->GetPayload());
    } catch (const std::exception &e) {
      logger_.Error("Failed to resolve TCP payload: " + std::string(e.what()), "❌");
    }
  }

  return elements;
}
