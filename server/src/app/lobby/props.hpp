/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <utility>

namespace rtype::server {
struct LobbyCtxProps {
  /// @brief Number of ticks for the game loop
  std::size_t ticks;

  /**
   * @brief Construct a new LobbyCtxProps object
   * @param ticks Number of ticks for the game loop
   */
  explicit LobbyCtxProps(std::size_t ticks) : ticks(ticks) {}

  /// @brief Construct a new LobbyCtxProps object with default values
  LobbyCtxProps() : ticks(0) {}
};
}  // namespace rtype::server
