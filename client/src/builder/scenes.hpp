/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scenes.hpp
*/

#pragma once

#include "libs/mew/src/game/game.hpp"

namespace rtype::client::builder {
class Scenes {
 public:
  /**
   * @brief Load the scenes of the game
   * @param game Game to load the scenes
   */
  static void LoadScenes(mew::game::Game &game);

  /**
   * @brief Set the entry scene of the game
   * @param game Game to set the entry scene
   */
  static void SetEntryScene(mew::game::Game &game);
};
}  // namespace rtype::client::builder
