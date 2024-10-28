/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <string>
#include <utility>

namespace rtype::server {
struct RoomCtxProps {
  /// @brief Number of ticks for the game loop
  std::size_t ticks;

  /// @brief Token to authenticate the room to the node
  std::string token;

  /**
   * @brief Construct a new LobbyCtxProps object
   * @param ticks Number of ticks for the game loop
   * @param token Token to authenticate the room to the node
   */
  explicit RoomCtxProps(std::size_t ticks, std::string token);

  /**
   * @brief Construct a new LobbyCtxProps object with default values
   */
  RoomCtxProps();
};
}  // namespace rtype::server
