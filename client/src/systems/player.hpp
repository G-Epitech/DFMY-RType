/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.hpp
*/

#pragma once
#include "managers/game_manager.hpp"
#include "managers/window_manager.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class PlayerSystem final : public ASystem<> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param window_manager The window manager to display the entities
   * @param game_manager The game manager to send messages to the server
   */
  PlayerSystem(const WindowManager::Ptr& window_manager, const GameManager::Ptr& game_manager);
  void Run(Registry::Ptr r) override;

 private:
  /// @brief The render window to display the entities.
  WindowManager::Ptr windowManager_;

  /// @brief The game manager to send messages to the server
  GameManager::Ptr gameManager_;

  bool isMovingUp_{false};
  bool isMovingDown_{false};
  bool isMovingLeft_{false};
  bool isMovingRight_{false};
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

  void ProcessPlayerMoveUp();
  void ProcessPlayerMoveDown();
  void ProcessPlayerMoveLeft();
  void ProcessPlayerMoveRight();
  void ProcessPlayerShoot();
};
}  // namespace rtype::client::systems
