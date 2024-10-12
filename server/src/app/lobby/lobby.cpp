/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.cpp
*/

#include "lobby.hpp"

#include <iostream>

using namespace rtype::server;

Lobby::Lobby(const BaseContext& ctx)
    : ctx_({ctx.name, ctx.port, ctx.type, std::get<LobbyCtxProps>(ctx.props)}),
      gameService_(ctx_.props.ticks) {}

int Lobby::Run() {
  gameService_.Run();
  return EXIT_SUCCESS;
}
