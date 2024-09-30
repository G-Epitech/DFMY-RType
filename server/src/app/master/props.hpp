/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <utility>

namespace rtype::server {
/// @brief Master context properties
struct MasterCtxProps {
  std::size_t maxGames;  // Maximum number of games the master can create
  std::size_t ticks;     // Number of ticks for the game loop for each game

  /**
   * @brief Construct a new MasterCtxProps object
   * @param maxGames maximum number of games the master can create
   * @param ticks number of ticks for the game loop for each game
   */
  MasterCtxProps(std::size_t maxGames, std::size_t ticks);

  /// @brief Construct a new MasterCtxProps object with default values
  MasterCtxProps();
};
}  // namespace rtype::server