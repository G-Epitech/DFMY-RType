/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** player.hpp
*/

#pragma once

#include <cstddef>

namespace rtype::sdk::game_core::stats {
struct Player {
  static float baseSpeed;
  static std::size_t maxHp;
};
}  // namespace rtype::sdk::game_core
