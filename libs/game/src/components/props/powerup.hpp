/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** powerup.hpp
*/

#pragma once

#include "libs/game/src/types/powerup.hpp"

namespace rtype::sdk::game::components {
enum class PowerupDuration {
  kShort = 0,
  kMedium = 1,
  kLong = 2,
};

enum class PowerupValue {
  kSmall = 0,
  kMedium = 1,
  kLarge = 2,
};

struct PowerupPropsComponent {
  types::PowerupType type;
  PowerupDuration duration;
  PowerupValue value;
};
}  // namespace rtype::sdk::game::components
