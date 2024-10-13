/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collision_layers.hpp
*/

#pragma once

#include <vector>

namespace rtype::sdk::game::constants {
/// @brief Collision layers for the game
enum CollisionLayers {
  kPlayer = 1 << 0,
  kEnemy = 1 << 1,
  kEnemyBullet = 1 << 2,
  kPlayerBullet = 1 << 3,
  kPowerUp = 1 << 5,
};

/// @brief Player collision layers
static const std::vector<int> kPlayerCollidesWith = {kEnemy, kEnemyBullet, kPowerUp};

/// @brief Enemy collision layers
static const std::vector<int> kEnemyCollidesWith = {kPlayer, kPlayerBullet};
}  // namespace rtype::sdk::game::constants