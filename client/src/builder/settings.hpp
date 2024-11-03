/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings.hpp
*/

#pragma once

#include "libs/mew/src/game/game.hpp"

namespace rtype::client::builder {
class Settings {
 public:
  /**
   * @brief Load the settings of the game
   * @param game Game to load the settings
   */
  static void LoadSettings(mew::game::Game *game);
};
}  // namespace rtype::client::builder
