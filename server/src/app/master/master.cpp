/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.cpp
*/

#include "master.hpp"

#include <iostream>

using namespace rtype::server;

Master::Master(const BaseContext& ctx) : ctx_() {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<MasterCtxProps>(ctx.props)};
}

int Master::Run() {
  std::cout << ctx_.name << std::endl;
  std::cout << ctx_.port << std::endl;
  std::cout << ctx_.type << std::endl;
  std::cout << ctx_.props.ticks << std::endl;
  std::cout << ctx_.props.maxGames << std::endl;
  return EXIT_SUCCESS;
}
