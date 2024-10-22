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
  constexpr static std::size_t damage = 10;
  /// @brief Fire rate of the weapon ( per projectile)
  constexpr static float fireRate = 3;
  /// @brief Speed of the weapon's projectiles
  constexpr static float projectileSpeed = 10;
};
}  // namespace rtype::sdk::game::stats
