/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** context.hpp
*/

#pragma once

#include <string>
#include <utility>
#include <variant>

#include "app/master/props.hpp"
#include "app/node/props.hpp"
#include "app/room/props.hpp"
#include "server_types.hpp"

namespace rtype::server {
/// @brief Context properties variant
using CtxProps = std::variant<RoomCtxProps, MasterCtxProps, NodeCtxProps>;

struct BaseContext {
  /// @brief Name of the server
  std::string name;
  /// @brief Port number of the server
  std::size_t port;
  /// @brief Server type
  ServerType type;
  /// @brief Server type-specific properties
  CtxProps props;

  /**
   * @brief Construct a new BaseContext object
   * @param name Name of the server
   * @param port Port number of the server
   * @param type Server type
   * @param props Server type-specific properties
   */
  BaseContext(std::string name, std::size_t port, ServerType type, CtxProps props);
};
}  // namespace rtype::server
