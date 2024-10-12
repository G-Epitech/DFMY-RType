/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** projectile.hpp
*/

#pragma once

#include "libs/game/src/types/projectile.hpp"

namespace rtype::sdk::game::components {
/// @brief Projectile properties component
struct ProjectilePropsComponent {
  /// @brief The speed of the projectile
  float speed;
  /// @brief The damage of the projectile
  int damage;
  /// @brief The type of the projectile
  types::ProjectileType type;
};
}  // namespace rtype::sdk::game::components
