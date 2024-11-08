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

class ChatTriggerSystem final : public ASystem<Tags> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param window_manager The window manager
   * @param settings_manager The settings manager
   */
  ChatTriggerSystem(WindowManager::Ptr window_manager, SettingsManager::Ptr settings_manager);

  void Run(Registry::Ptr r, zipper<Tags> components) override;

 private:
  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /// @brief Settings manager
  SettingsManager::Ptr settingsManager_;

  /**
   * @brief Check if the chat open key is pressed
   * @param event The event
   * @return true if the chat open key is pressed, false otherwise
   */
  static bool IsChatOpenKey(const sf::Event& event);

  /**
   * @brief Check if the chat close key is pressed
   * @param event The event
   * @return true if the chat close key is pressed, false otherwise
   */
  static bool IsChatCloseKey(const sf::Event& event);
};
}  // namespace rtype::client::systems
