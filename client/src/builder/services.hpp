/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** services.hpp
*/

#pragma once

#include "libs/mew/src/game/builder.hpp"

namespace rtype::client::builder {
class Services {
 public:
  /**
   * @brief Load the services of the game
   * @param builder Game to load the services
   */
  static void RegisterServices(mew::game::GameBuilder *builder);
};
}  // namespace rtype::client::builder
