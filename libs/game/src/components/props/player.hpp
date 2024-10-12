/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_props.hpp
*/

#pragma once

namespace rtype::sdk::game::components {
/// @brief Player properties component
struct PlayerPropsComponent {
  /// @brief The speed of the player
  float speed;
  /// @brief The health of the player
  int hp;
  /// @brief The fire rate of the player
  float fireRate;
};
}  // namespace rtype::sdk::game::components
