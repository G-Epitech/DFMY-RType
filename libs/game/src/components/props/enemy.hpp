/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_props.hpp
*/

#pragma once

namespace rtype::sdk::game::components {
/// @brief Enemy properties component
struct EnemyPropsComponent {
  /// @brief The speed of the enemy
  float speed;
  /// @brief The health of the enemy
  int hp;
  /// @brief The fire rate of the enemy
  float fireRate;
};
}  // namespace rtype::sdk::game::components
