/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.cpp
*/

#include "./room.hpp"

#include <iostream>

rtype::server::Room::Room(const BaseContext &ctx)
    : ctx_({ctx.name, ctx.port, ctx.type, std::get<RoomCtxProps>(ctx.props)}),
      api_(std::make_shared<rtype::sdk::game::api::Lobby>(
          ctx_.port, [this](std::uint64_t id) { this->gameService_.NewPlayer(id); })),
      gameService_(ctx_.props.ticks) {}

int rtype::server::Room::Run() {
  gameService_.Run(api_);
  return EXIT_SUCCESS;
}
