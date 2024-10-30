/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** difficulty.hpp
*/

#pragma once

#include <string>

namespace rtype::server::game {
struct DifficultyPlayerMultipliers {
  float health;
  float speed;
  float fireRate;
  float damage;
};

struct DifficultyEnemyMultipliers {
  float health;
  float speed;
  float fireRate;
  float damage;
};

struct DifficultyMultipliers {
  DifficultyPlayerMultipliers player;
  DifficultyEnemyMultipliers enemy;
};

struct Difficulty {
  std::string name;
  std::string description;
  DifficultyMultipliers multipliers;
};
}  // namespace rtype::server::game
