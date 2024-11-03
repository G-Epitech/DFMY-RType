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
      api_(std::make_shared<rtype::sdk::game::api::Room>(
          ctx_.port, [this](std::uint64_t id) { this->gameService_.NewPlayer(id); },
          std::get<RoomCtxProps>(ctx.props).id)),
      gameService_(ctx_.props.ticks, ctx_.props.difficulty) {}

int rtype::server::Room::Run() {
  api_->RegisterNewRoom();

  auto result = gameService_.Initialize();
  if (result == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (gameService_.GetNbPlayers() >= ctx_.props.maxPlayers) {
      api_->StartGame();
      break;
    }
  }

  gameService_.Run(api_);
  return EXIT_SUCCESS;
}
