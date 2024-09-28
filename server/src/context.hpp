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

#include "allocator/props.hpp"
#include "lobby/props.hpp"
#include "server_types.hpp"

namespace rtype::server {

using CtxProps = std::variant<LobbyCtxProps, AllocatorCtxProps>;

struct BaseContext {
  std::string name;  // Name of the server context
  std::size_t port;  // Port number
  ServerType type;   // Server type
  CtxProps props;

  BaseContext(std::string name, std::size_t port, ServerType type, CtxProps props)
      : name(std::move(name)), port(port), type(type), props(props) {}
};
}  // namespace rtype::server
