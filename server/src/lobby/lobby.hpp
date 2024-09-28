/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/context.hpp"

namespace rtype::server {
class Lobby {
 public:
  explicit Lobby(const BaseContext& ctx);
  ~Lobby() = default;

 private:
  struct Context {
    std::string name;
    std::size_t port;
    ServerType type;
    LobbyCtxProps props;
  };

 private:
  Context mCtx;
};

}  // namespace rtype::server
