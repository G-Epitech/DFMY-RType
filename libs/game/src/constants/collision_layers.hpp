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
static const std::vector<int> kPlayerCollisionLayers = {kPlayer};
static const std::vector<int> kPlayerIncludeLayers = {kEnemy, kEnemyBullet, kPowerUp};

/// @brief Enemy collision layers
static const std::vector<int> kEnemyCollisionLayers = {kEnemy};
static const std::vector<int> kEnemyIncludeLayers = {kPlayer, kPlayerBullet};

/// @brief Enemy bullet collision layers
static const std::vector<int> kEnemyBulletCollisionLayers = {kEnemyBullet};
static const std::vector<int> kEnemyBulletIncludeLayers = {kPlayer};

/// @brief Player bullet collision layers
static const std::vector<int> kPlayerBulletCollisionLayers = {kPlayerBullet};
static const std::vector<int> kPlayerBulletIncludeLayers = {kEnemy};

}  // namespace rtype::sdk::game::constants
