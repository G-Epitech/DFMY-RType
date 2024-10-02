/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_start.hpp
*/

#pragma once

#include <cstddef>
#include <string>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Game start payload
struct EXPORT_API_COMMON_SDK_API GameStart {
  /// @brief Number of players in the game
  std::size_t nbPlayers;
  /// @brief Message to display to the players
  std::string message;

  /**
   * @brief Construct a new Game Start object
   * @param nbPlayers Number of players
   * @param message Message to display
   */
  GameStart(std::size_t nbPlayers, std::string message);
};
}  // namespace rtype::sdk::api_common::payload
