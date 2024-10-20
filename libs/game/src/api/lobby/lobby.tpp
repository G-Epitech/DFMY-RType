/*
** EPITECH PROJECT, 2024
** lobby.tpp
** File description:
** lobby class
*/

#pragma once

using namespace rtype::sdk::game::api;
using namespace abra::tools;

template<typename T>
bool Lobby::SendPayloadTCP(const MessageLobbyType &type, const T &payload) {
  this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send TCP packet of type " + std::to_string(type), "📦");

  auto success = this->serverTCP_.Send(packet, this->masterId_) == SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}

template<typename T>
bool Lobby::SendPayloadsUDP(const MessageLobbyType &type, const T &payload) {
    this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
    auto packets = this->packetBuilder_.Build(payload);

    logger_.Info("Send " + std::to_string(packets.size()) + " packets to " +
                 std::to_string(this->clients_.size()) + " players in lobby the lobby 📦");

    for (const auto &player: this->clients_) {
      for (const auto &packet: packets) {
        auto success = this->serverUDP_.Send(packet, player.endpoint) == SendMessageStatus::kSuccess;
        if (!success) {
          logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");
        }
      }
    }

    return true;
}
