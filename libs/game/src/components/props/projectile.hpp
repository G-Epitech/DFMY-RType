/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** projectile.hpp
*/

#pragma once

#include "libs/game/src/types/projectile.hpp"

namespace rtype::sdk::game::components {
struct ProjectilePropsComponent {
  float speed;
  int damage;
  types::ProjectileType type;
};
}  // namespace rtype::sdk::game::components
