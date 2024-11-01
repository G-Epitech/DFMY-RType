/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** difficulty.hpp
*/

#pragma once

#include <string>

namespace rtype::server::game {
/// @brief Multipliers for player stats
struct DifficultyPlayerMultipliers {
  float health;
  float speed;
  float fireRate;
  float damage;
};

/// @brief Multipliers for enemy stats
struct DifficultyEnemyMultipliers {
  float health;
  float speed;
  float fireRate;
  float damage;
};

/// @brief Multipliers for player and enemy stats
struct DifficultyMultipliers {
  DifficultyPlayerMultipliers player;
  DifficultyEnemyMultipliers enemy;
};

struct Difficulty {
  /// @brief Name of the difficulty
  std::string name;
  /// @brief Description of the difficulty
  std::string description;
  /// @brief Multipliers for player and enemy stats
  DifficultyMultipliers multipliers;
};
}  // namespace rtype::server::game
