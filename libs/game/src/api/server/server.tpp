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
bool Server::SendPayloadTCP(const MessageServerType &type, const T &payload, const std::uint64_t &clientId) {
  this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send TCP packet of type " + std::to_string(type), "📦");

  auto success = this->serverTCP_.Send(packet, clientId) == SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}
