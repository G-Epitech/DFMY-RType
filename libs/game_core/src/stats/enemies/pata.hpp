/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** pala.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game_core/src/api.hpp"

namespace rtype::sdk::game_core::stats {
/// @brief Pata enemy stats
struct EXPORT_GAME_CORE_SDK_API Pata {
  /// @brief Damage dealt by the enemy
  static std::size_t damage;
  /// @brief Fire rate of the enemy (projectiles per second)
  static std::size_t fireRate;
  /// @brief Speed of the enemy's projectiles
  static float projectileSpeed;
  /// @brief Maximum health points of the enemy
  static std::size_t maxHp;
  /// @brief Speed of the enemy
  static float speed;
};
};  // namespace rtype::sdk::game_core::stats
