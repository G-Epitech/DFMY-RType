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

  /// @brief If of the room
  std::size_t id;

  /// @brief Max players in the room
  std::size_t maxPlayers;

  /// @brief Difficulty of the room
  std::size_t difficulty;

  /**
   * @brief Construct a new LobbyCtxProps object
   * @param ticks Number of ticks for the game loop
   * @param token Token to authenticate the room to the node
   */
  explicit RoomCtxProps(std::size_t ticks, std::string token, std::size_t id, std::size_t maxPlayers, std::size_t difficulty);

  /**
   * @brief Construct a new LobbyCtxProps object with default values
   */
  RoomCtxProps();
};
}  // namespace rtype::server
