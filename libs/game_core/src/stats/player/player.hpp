/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** player.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game_core/src/api.hpp"

namespace rtype::sdk::game_core::stats {
/// @brief Player stats
struct EXPORT_GAME_CORE_SDK_API Player {
  /// @brief Base speed of the player
  static float baseSpeed;
  /// @brief Base maximum health points of the player
  static std::size_t baseMaxHp;
};
}  // namespace rtype::sdk::game_core::stats
