/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.cpp
*/

#include "master.hpp"

#include <iostream>

using namespace rtype::server;

Master::Master(const BaseContext &ctx) : ctx_(), api_(static_cast<int>(ctx.port)) {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<MasterCtxProps>(ctx.props)};
}

int Master::Run() {
  // LOBBY TEST UNTIL NODE SYSTEM (PLEASE START A LOBBY SERVER BEFORE)
  api_.CreateLobby("lobby1", 30000);

  api_.Join();
  return EXIT_SUCCESS;
}
