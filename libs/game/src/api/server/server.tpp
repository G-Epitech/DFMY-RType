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

template<typename T>
bool Server::SendPayloadsToLobby(const rtype::sdk::game::api::MessageServerType &type, const std::vector<T> &payload,
                                 const std::uint64_t &lobbyId) {
  this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
  auto packets = this->packetBuilder_.Build(payload);

  logger_.Info("Send " + std::to_string(packets.size()) + " packets to " +
               std::to_string(this->lobbies_[lobbyId].clients.size()) + " players in lobby " + std::to_string(lobbyId),
               "📦");

  for (const auto &player: this->lobbies_[lobbyId].clients) {
    for (const auto &packet: packets) {
      auto success = this->lobbies_[lobbyId].serverUDP->Send(packet, player.endpoint) == SendMessageStatus::kSuccess;
      if (!success) {
        logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");
      }
    }
  }

  return true;
}
