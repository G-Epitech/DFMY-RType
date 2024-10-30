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
struct WaveEnemy {
  std::string name;
  int count;
};

struct Wave {
  float maxTime;
  std::vector<WaveEnemy> enemies;
};

struct Level {
  std::string name;
  std::string description;
  std::vector<Wave> waves;
};
}  // namespace rtype::server::game
