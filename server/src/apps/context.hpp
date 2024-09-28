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

#include "director/props.hpp"
#include "lobby/props.hpp"
#include "src/server_types.hpp"

namespace rtype::server {

using CtxProps = std::variant<LobbyCtxProps, DirectorCtxProps>;

struct BaseContext {
  std::string name;  // Name of the server context
  std::size_t port;  // Port number
  ServerType type;   // Server type
  CtxProps props;

  BaseContext(std::string name, std::size_t port, ServerType type, CtxProps props)
      : name(std::move(name)), port(port), type(type), props(props) {}
};
}  // namespace rtype::server
