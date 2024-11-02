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
   */
  ChatMessagesSystem(WindowManager::Ptr window_manager,
                     services::ServerConnectionService::Ptr server_connection_service);

  void Run(Registry::Ptr r) override;

 private:
  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Last messages
  std::vector<Entity> oldMessages_;

  /**
   * @brief Move all positions of the messages
   * @param r The registry
   */
  void MoveAllPositions(Registry::Ptr r);

  /**
   * @brief Add a message to the chat
   * @param r The registry
   * @param message The message to add
   */
  void AddMesage(const Registry::Ptr &r, const api::payload::ChatMessage &message);
};
}  // namespace rtype::client::systems
