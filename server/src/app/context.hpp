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

#include "master/props.hpp"
#include "lobby/props.hpp"
#include "server_types.hpp"

namespace rtype::server {
/// @brief Context properties variant
using CtxProps = std::variant<LobbyCtxProps, MasterCtxProps>;

struct BaseContext {
  std::string name;  // Name of the server
  std::size_t port;  // Port number of the server
  ServerType type;   // Server type
  CtxProps props;    // Server type-specific properties

  /**
   * @brief Construct a new BaseContext object
   * @param name Name of the server
   * @param port Port number of the server
   * @param type Server type
   * @param props Server type-specific properties
   */
  BaseContext(std::string name, std::size_t port, ServerType type, CtxProps props)
      : name(std::move(name)), port(port), type(type), props(props) {}
};
}  // namespace rtype::server
