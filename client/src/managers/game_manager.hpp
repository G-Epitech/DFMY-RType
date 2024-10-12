/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game_manager.hpp
*/

#pragma once

#include <memory>

#include "game/keymap.hpp"

namespace rtype::client {
class GameManager {
 public:
  /// @brief Pointer to a game manager
  typedef std::shared_ptr<GameManager> Ptr;

  /**
   * @brief Create a new game manager
   * @return Pointer to the game manager
   */
  static Ptr Create();

  /**
   * @brief Construct a new Window Manager object
   */
  GameManager();

  /**
   * @brief Construct a new Window Manager object
   */
  ~GameManager();

  void EnableAnimation();

  void DisableAnimation();

  [[nodiscard]] bool GetAnimationStatus() const;

  /// @brief Key map
  KeyMap keyMap = KeyMap::ZQSD;

 private:
  /// @brief Enable or disable animations.
  bool animations_ = true;
};
}  // namespace rtype::client
