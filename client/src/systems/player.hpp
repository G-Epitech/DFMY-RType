/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.hpp
*/

#pragma once
#include "context/global.hpp"
#include "managers/game_manager.hpp"
#include "managers/window_manager.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class PlayerSystem final : public ASystem<> {
 public:
  /**
   * @brief Default constructor of a Player System
   * @param context The global context of the game
   */
  explicit PlayerSystem(const GlobalContext &context);

  void Run(Registry::Ptr r) override;

 private:
  /// @brief Global context of the game
  const GlobalContext &context_;

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
