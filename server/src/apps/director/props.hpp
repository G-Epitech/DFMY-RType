/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <utility>

namespace rtype::server {
/// @brief Director context properties
struct DirectorCtxProps {
  std::size_t maxGames;  // Maximum number of games the director can create
  std::size_t ticks;     // Number of ticks for the game loop for each game

  /**
   * @brief Construct a new DirectorCtxProps object
   * @param maxGames maximum number of games the director can create
   * @param ticks number of ticks for the game loop for each game
   */
  DirectorCtxProps(std::size_t maxGames, std::size_t ticks) : maxGames(maxGames), ticks(ticks) {}

  /// @brief Construct a new DirectorCtxProps object with default values
  DirectorCtxProps() : maxGames(0), ticks(0) {}
};
}  // namespace rtype::server
