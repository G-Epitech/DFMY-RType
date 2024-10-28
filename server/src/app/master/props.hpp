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
struct MasterCtxProps {
  /// @brief The token that allow a node to connect to the master
  std::string token;

  /**
   * @brief Construct a new MasterCtxProps object
   * @param token The token that allow a node to connect to the master
   */
  MasterCtxProps(std::string token);

  /**
   * @brief Construct a new MasterCtxProps object with default values
   */
  MasterCtxProps();
};
}  // namespace rtype::server
