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

namespace rtype::client::systems {

using namespace mew::managers;

class PlayerSystem final : public ASystem<> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param settings_manager The settings manager
   * @param window_manager The window manager
   * @param server_connection_service The server connection service
   */
  PlayerSystem(SettingsManager::Ptr settings_manager, WindowManager::Ptr window_manager,
               services::ServerConnectionService::Ptr server_connection_service);

  void Run(Registry::Ptr r) override;

 private:
  /// @brief Settings manager of the game
  SettingsManager::Ptr settingsManager_;

  /// @brief Window manager of the game
  WindowManager::Ptr windowManager_;

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /**
   * @brief Store moving up action state
   */

  /**
   * @brief Store moving up action state
   */
  bool isMovingUp_{false};

  /**
   * @brief Store moving down action state
   */
  bool isMovingDown_{false};

  /**
   * @brief Store moving left action state
   */
  bool isMovingLeft_{false};

  /**
   * @brief Store moving right action state
   */
  bool isMovingRight_{false};

  /**
   * @brief Store shooting action state
   */
  bool isShooting_{false};

  /**
   * @brief Update the player actions
   * @param action The action to update
   * @param isPressed If the action is pressed or not
   */
  void UpdatePlayerActions(const GameAction& action, const bool& isPressed);

  /**
   * @brief Process the player actions
   */
  void ProcessPlayerActions();

  /**
   * @brief Process the player move up action
   */
  void ProcessPlayerMoveUp();

  /**
   * @brief Process the player move down action
   */
  void ProcessPlayerMoveDown();

  /**
   * @brief Process the player move left action
   */
  void ProcessPlayerMoveLeft();

  /**
   * @brief Process the player move right action
   */
  void ProcessPlayerMoveRight();

  /**
   * @brief Process the player shoot action
   */
  void ProcessPlayerShoot();
};
}  // namespace rtype::client::systems
