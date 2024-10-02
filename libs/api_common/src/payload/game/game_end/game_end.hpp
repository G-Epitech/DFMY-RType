/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_end.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Game end stats
struct EXPORT_API_COMMON_SDK_API CoopGameEnd {
  /// @brief Score of the player
  std::size_t score;
  /// @brief Time taken to finish the game
  time_t time;
  /// @brief Whether the player won or not
  bool win;

  /**
   * @brief Construct a new Coop Game End object
   * @param score score of the player
   * @param time time taken to finish the game
   * @param win whether the player won or not
   */
  CoopGameEnd(std::size_t score, time_t time, bool win);
};
}  // namespace rtype::sdk::api_common::payload
