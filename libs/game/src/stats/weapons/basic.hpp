/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** basic.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game::stats {
/// @brief Main player weapon stats
struct WeaponBasic {
  /// @brief Damage dealt by the weapon
  inline static std::size_t damage = 10;
  /// @brief Fire rate of the weapon (projectiles per second)
  inline static std::size_t fireRate = 20;
  /// @brief Speed of the weapon's projectiles
  inline static float projectileSpeed = 10;
};
}  // namespace rtype::sdk::game::stats
