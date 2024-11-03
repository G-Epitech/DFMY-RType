/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** message_handler.hpp
*/

#pragma once

#include "libs/game/includes/api.hpp"
#include "registry.hpp"

namespace rtype::server::game::network {
class MessageHandler {
 public:
  MessageHandler();
  ~MessageHandler() = default;

  /**
   * @brief Run the message handler
   * @param registry Registry instance
   * @param api Room API
   * @param players Players in the room
   */
  void Run(const std::shared_ptr<zygarde::Registry>& registry,
           const std::shared_ptr<rtype::sdk::game::api::Room>& api,
           const std::map<std::uint64_t, zygarde::Entity>& players);

 private:
  /**
   * @brief Handle a player message
   * @param player Player data
   * @param data Message data
   * @param registry Registry instance
   */
  void HandlePlayerMessage(const std::pair<std::uint64_t, zygarde::Entity>& player,
                           const abra::server::ClientUDPMessage& data,
                           const std::shared_ptr<zygarde::Registry>& registry);

  /**
   * @brief Handle a player move message
   * @param player Player data
   * @param data Message data
   * @param registry Registry instance
   */
  void HandlePlayerMoveMessage(const std::pair<std::uint64_t, zygarde::Entity>& player,
                               const abra::server::ClientUDPMessage& data,
                               const std::shared_ptr<zygarde::Registry>& registry);

  /**
   * @brief Handle a player shoot message
   * @param player Player data
   * @param data Message data
   * @param registry Registry instance
   */
  void HandlePlayerShootMessage(const std::pair<std::uint64_t, zygarde::Entity>& player,
                                const abra::server::ClientUDPMessage& data,
                                const std::shared_ptr<zygarde::Registry>& registry);

 private:
  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;
  /// @brief Logger
  Logger logger_;
};
}  // namespace rtype::server::game::network
