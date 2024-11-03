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
using namespace mew::sets::drawable;

namespace rtype::client::systems {

class ChatInputSystem final : public ASystem<Tags, Drawable> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param window_manager The window manager
   * @param server_connection_service The server connection service
   */
  ChatInputSystem(WindowManager::Ptr window_manager,
                  services::ServerConnectionService::Ptr server_connection_service);

  void Run(Registry::Ptr r, zipper<Tags, Drawable> components) override;

 private:
  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;
};
}  // namespace rtype::client::systems
