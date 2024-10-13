/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.cpp
*/

#include "lobby.hpp"

#include <iostream>

using namespace rtype::server;

Lobby::Lobby(const BaseContext &ctx)
        : ctx_({ctx.name, ctx.port, ctx.type, std::get<LobbyCtxProps>(ctx.props)}),
          api_(std::make_shared<rtype::sdk::game::api::Server>(ctx_.port)),
          gameService_(ctx_.props.ticks) {}

int Lobby::Run() {
  auto id = api_->CreateLobby(ctx_.name, [this](std::uint64_t id) {
    this->gameService_.NewPlayer(id);
  });

  gameService_.Run(id, api_);
  return EXIT_SUCCESS;
}
