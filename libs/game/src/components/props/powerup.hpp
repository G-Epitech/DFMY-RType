/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** powerup.hpp
*/

#pragma once

#include "libs/game/src/types/powerup.hpp"

namespace rtype::sdk::game::components {
/// @brief Powerup duration enum
enum class PowerupDuration {
  kShort = 0,
  kMedium = 1,
  kLong = 2,
};

/// @brief Powerup value enum
enum class PowerupValue {
  kSmall = 0,
  kMedium = 1,
  kLarge = 2,
};

/// @brief Powerup properties component
struct PowerupPropsComponent {
  /// @brief The type of the powerup
  types::PowerupType type;
  /// @brief The duration of the powerup
  PowerupDuration duration;
  /// @brief The value of the powerup
  PowerupValue value;
};
}  // namespace rtype::sdk::game::components
