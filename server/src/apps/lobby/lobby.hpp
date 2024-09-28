/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {
class Lobby final : public IServer {
 public:
  explicit Lobby(const BaseContext& ctx);
  ~Lobby() override = default;

  int Run() override;

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
