/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level.hpp
*/

#pragma once

#include <string>
#include <vector>

namespace rtype::server::game {
/// @brief Structure representing an enemy in a wave
struct WaveEnemy {
  /// @brief Name of the enemy
  std::string name;
  /// @brief Amount of enemies that will spawn during the wave
  int count;
};

struct Wave {
  /// @brief Duration of the wave (before the next wave starts)
  float maxTime;
  /// @brief Enemies that will spawn during the wave (name, count)
  std::map<std::string, int> enemies;
};

struct Level {
  /// @brief Name of the level
  std::string name;
  /// @brief Description of the level
  std::string description;
  /// @brief Waves of enemies that will spawn during the level
  std::vector<Wave> waves;
};
}  // namespace rtype::server::game
