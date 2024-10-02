/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** player.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game_stats/src/api.hpp"

namespace rtype::sdk::game::stats {
/// @brief Player stats
struct EXPORT_GAME_STATS_SDK_API Player {
  /// @brief Base speed of the player
  static float baseSpeed;
  /// @brief Base maximum health points of the player
  static std::size_t baseMaxHp;
};
}  // namespace rtype::sdk::game::stats
