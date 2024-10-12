/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** player.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game::constants::stats {
/// @brief Player stats
struct Player {
  /// @brief Base speed of the player
  inline static float speed = 10;
  /// @brief Base maximum health_update points of the player
  inline static std::size_t maxHp = 100;
};
}  // namespace rtype::sdk::game::constants::stats
