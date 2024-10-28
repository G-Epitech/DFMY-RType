/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.cpp
*/

#include "server/src/app/master/master.hpp"

#include <iostream>

rtype::server::Master::Master(const BaseContext &ctx)
    : ctx_(),
      api_(static_cast<int>(ctx.port),
           static_cast<int>(std::get<MasterCtxProps>(ctx.props).nodePort)) {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<MasterCtxProps>(ctx.props)};
}

int rtype::server::Master::Master::Run() {
  api_.Join();
  return EXIT_SUCCESS;
}
