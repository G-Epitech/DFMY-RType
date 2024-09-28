/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** director.cpp
*/

#include "director.hpp"

#include <iostream>

using namespace rtype::server;

Director::Director(const BaseContext& ctx) : mCtx() {
  mCtx = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<DirectorCtxProps>(ctx.props)};
}

int Director::Run() {
  std::cout << mCtx.name << std::endl;
  std::cout << mCtx.port << std::endl;
  std::cout << mCtx.type << std::endl;
  std::cout << mCtx.props.ticks << std::endl;
  std::cout << mCtx.props.maxGames << std::endl;
  return EXIT_SUCCESS;
}
