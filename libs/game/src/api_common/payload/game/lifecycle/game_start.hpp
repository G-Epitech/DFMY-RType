/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_start.hpp
*/

#pragma once

#include <cstddef>
#include <string>

namespace rtype::sdk::game::api_common::payload {
/// @brief Game start payload
struct GameStart {
  /// @brief Number of players in the game
  std::size_t nbPlayers;
  /// @brief Message to display to the players
  std::string message;
};
}  // namespace rtype::sdk::game::api_common::payload
