/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.hpp
*/

#pragma once

#include "client/src/game/keymap.hpp"
#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/managers/managers.hpp"
#include "libs/zygarde/src/system_abstract.hpp"

using namespace mew::managers;
using namespace zygarde::core::components;

namespace rtype::client::systems {

class ChatMessagesSystem final : public ASystem<> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param window_manager The window manager
   * @param server_connection_service The server connection service
   * @param username The username of the player
   */
  ChatMessagesSystem(WindowManager::Ptr window_manager,
                     services::ServerConnectionService::Ptr server_connection_service,
                     const std::string &username, const Registry::Ptr &r);

  void Run(Registry::Ptr r) override;

 private:
  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Last messages entites with their time
  std::map<Entity, std::chrono::time_point<std::chrono::system_clock>> oldMessages_;

  /**
   * @brief Move all positions of the messages
   * @param r The registry
   */
  void MoveAllPositions(const Registry::Ptr &r);

  /**
   * @brief Add a message to the chat
   * @param r The registry
   * @param message The message to add
   */
  void AddMessage(const Registry::Ptr &r, const api::payload::ChatMessage &message);

  /**
   * @brief Add a username to the chat
   * @param r The registry
   * @param message The message to add
   */
  void AddUsername(const Registry::Ptr &r, const api::payload::ChatMessage &message);

  /**
   * @brief Cleanup old messages
   * @param r The registry
   */
  void CleanupOldMessages(const Registry::Ptr &r);
};
}  // namespace rtype::client::systems
