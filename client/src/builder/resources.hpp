/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** resources.cpp
*/

#include "libs/mew/src/game/game.hpp"

namespace rtype::client::builder {
class Resources {
 public:
  /**
   * @brief Load the resources of the game
   * @param game Game to load the resources
   */
  static void LoadResources(mew::game::Game &game);
};
}  // namespace rtype::client::builder
