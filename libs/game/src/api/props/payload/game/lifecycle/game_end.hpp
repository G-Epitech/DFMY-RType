/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_end.hpp
*/

#pragma once

#include <cstddef>
#include <ctime>

namespace rtype::sdk::game::api::payload {
/// @brief Game end stats
struct CoopGameEnd {
  /// @brief Score of the player
  std::size_t score;
  /// @brief Time taken to finish the game
  time_t time;
  /// @brief Whether the player won or not
  bool win;
};
}  // namespace rtype::sdk::game::api::payload
