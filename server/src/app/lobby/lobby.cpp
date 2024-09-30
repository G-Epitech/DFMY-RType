/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.cpp
*/

#include "lobby.hpp"

#include <iostream>

using namespace rtype::server;

Lobby::Lobby(const BaseContext& ctx) : ctx_() {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<LobbyCtxProps>(ctx.props)};
}

int Lobby::Run() {
  std::cout << ctx_.name << std::endl;
  std::cout << ctx_.port << std::endl;
  std::cout << ctx_.type << std::endl;
  std::cout << ctx_.props.ticks << std::endl;
  return EXIT_SUCCESS;
}
