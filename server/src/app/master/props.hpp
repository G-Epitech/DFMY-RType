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

  /// @brief The node port
  std::size_t nodePort;

  /// @brief The database host
  std::string dbHost;

  /// @brief The database port
  std::string dbPort;

  /// @brief The database username
  std::string dbUsername;

  /// @brief The database password
  std::string dbPassword;

  /// @brief The database name
  std::string dbName;

  /**
   * @brief Construct a new MasterCtxProps object
   * @param token The token that allow a node to connect to the master
   */
  MasterCtxProps(std::string token, std::size_t nodePort, std::string dbHost, std::string dbPort,
                 std::string dbUsername, std::string dbPassword, std::string dbName);

  /**
   * @brief Construct a new MasterCtxProps object with default values
   */
  MasterCtxProps();
};
}  // namespace rtype::server
