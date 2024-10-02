/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** basic.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game_core/src/api.hpp"

namespace rtype::sdk::game_core::stats {
/// @brief Main player weapon stats
struct EXPORT_GAME_CORE_SDK_API WeaponMain {
  /// @brief Damage dealt by the weapon
  static std::size_t damage;
  /// @brief Fire rate of the weapon (projectiles per second)
  static std::size_t fireRate;
  /// @brief Speed of the weapon's projectiles
  static float projectileSpeed;
};
}  // namespace rtype::sdk::game_core::stats
