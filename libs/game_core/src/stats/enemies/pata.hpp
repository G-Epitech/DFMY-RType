/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** pala.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game_core::stats {
struct Pata {
  static std::size_t damage;
  static std::size_t fireRate;
  static float projectileSpeed;
  static std::size_t maxHp;
  static float speed;
};
};  // namespace rtype::sdk::game_core::stats
