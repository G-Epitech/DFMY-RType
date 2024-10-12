/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** powerup.hpp
*/

#pragma once

namespace rtype::sdk::game::types {
/// @brief Enum of the different types of powerup
enum class PowerupType {
  kHealth = 0,
  kShield = 1,
  kSpeed = 2,
  kDamage = 3,
  kFireRate = 4,
  kInvincibility = 5,
};
}  // namespace rtype::sdk::game::types
