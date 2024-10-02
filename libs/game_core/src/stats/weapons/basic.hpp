/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** basic.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game_core::stats {
struct WeaponMain {
  static std::size_t damage;
  static std::size_t fireRate;
  static float projectileSpeed;
};
}  // namespace rtype::sdk::game_core
