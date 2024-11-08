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
  kPlayer = 1,
  kEnemy = 2,
  kEnemyBullet = 4,
  kPlayerBullet = 8,
  kPowerUp = 16,
};

/// @brief Player collision layers
static const std::vector<int> kPlayerCollisionLayers = {kPlayer};
static const std::vector<int> kPlayerIncludeLayers = {kEnemy, kEnemyBullet, kPowerUp};

/// @brief Enemy collision layers
static const std::vector<int> kEnemyCollisionLayers = {kEnemy};
static const std::vector<int> kEnemyIncludeLayers = {kPlayer, kPlayerBullet};

/// @brief Enemy bullet collision layers
static const std::vector<int> kEnemyBulletCollisionLayers = {kEnemyBullet};
static const std::vector<int> kEnemyBulletIncludeLayers = {kPlayer, kPlayerBullet};

/// @brief Player bullet collision layers
static const std::vector<int> kPlayerBulletCollisionLayers = {kPlayerBullet};
static const std::vector<int> kPlayerBulletIncludeLayers = {kEnemy, kEnemyBullet};

}  // namespace rtype::sdk::game::constants
