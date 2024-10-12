/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game_manager.hpp
*/

#pragma once

#include <memory>

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
};
}  // namespace rtype::client
