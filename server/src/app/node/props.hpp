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
/// @brief Master context properties
struct NodeCtxProps {
  /// @brief The maximum number of rooms that can be created
  std::size_t maxRooms;

  /// @brief The token that allow a room to connect to the node
  std::string token;

  /// @brief The token to connect to the master
  std::string masterToken;

  /// @brief The path to the binary
  std::string binaryPath;

  /// @brief The ip of the node
  std::string ip;

  /**
   * @brief Construct a new NodeCtxProps object
   * @param token The token that allow a room to connect to the node
   */
  NodeCtxProps(std::size_t maxRooms, std::string token, std::string masterToken,
               std::string binaryPath, std::string ip);

  /**
   * @brief Construct a new NodeCtxProps object with default values
   */
  NodeCtxProps();
};
}  // namespace rtype::server
