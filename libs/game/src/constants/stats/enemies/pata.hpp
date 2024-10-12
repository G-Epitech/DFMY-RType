/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** pala.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game::constants::stats {
/// @brief Pata enemy stats
struct Pata {
  /// @brief Damage dealt by the enemy
  inline static std::size_t damage = 5;
  /// @brief Fire rate of the enemy (projectiles per second)
  inline static std::size_t fireRate = 10;
  /// @brief Speed of the enemy's projectiles
  inline static float projectileSpeed = 10;
  /// @brief Maximum health_update points of the enemy
  inline static std::size_t maxHp = 30;
  /// @brief Speed of the enemy
  inline static float speed = 10;
};
};  // namespace rtype::sdk::game::constants::stats
