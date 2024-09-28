/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** allocator.cpp
*/

#include "allocator.hpp"

#include <iostream>

using namespace rtype::server;

Allocator::Allocator(const BaseContext& ctx) : mCtx() {
  mCtx = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<AllocatorCtxProps>(ctx.props)};
}

int Allocator::Run() {
  std::cout << mCtx.name << std::endl;
  std::cout << mCtx.port << std::endl;
  std::cout << mCtx.type << std::endl;
  std::cout << mCtx.props.ticks << std::endl;
  std::cout << mCtx.props.maxGames << std::endl;
  return 0;
}
