/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.cpp
*/

#include "lobby.hpp"

#include <iostream>

using namespace rtype::server;

Lobby::Lobby(const BaseContext& ctx) : mCtx() {
  mCtx = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<LobbyCtxProps>(ctx.props)};
  std::cout << mCtx.name << std::endl;
  std::cout << mCtx.port << std::endl;
  std::cout << mCtx.type << std::endl;
  std::cout << mCtx.props.ticks << std::endl;
}
