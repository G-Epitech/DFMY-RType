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
  this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send packet (TCP) of type " + std::to_string(type), "📦");

  auto success = this->clientTCP_.Send(packet) == abt::SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}

template <typename T>
bool api::Client::SendPayloadUDP(const ClientToRoomMsgType &type, const T &payload) {
  if (!this->clientUDP_.has_value())
    return false;

  this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send packet (UDP) of type " + std::to_string(type), "📦");

  auto success = this->clientUDP_->Send(packet) == abt::SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}

template <typename T>
std::vector<T> api::Client::ResolveUDPPayloads(RoomToClientMsgType type, const ServerMessage &message) {
  if (message.messageType != type || message.protocolType != NetworkProtocolType::kUDP) {
    return {};
  }
  auto elements = std::vector<T>();

  for (auto &data : message.data) {
    auto packet = this->packetBuilder_.Build<T>(data);
    elements.push_back(packet->GetPayload());
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
    auto packet = this->packetBuilder_.Build<T>(data);
    elements.push_back(packet->GetPayload());
  }

  return elements;
}
