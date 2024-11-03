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
           static_cast<int>(std::get<MasterCtxProps>(ctx.props).nodePort),
           std::get<MasterCtxProps>(ctx.props).token,
           {
               .host = std::get<MasterCtxProps>(ctx.props).dbHost,
               .port = std::get<MasterCtxProps>(ctx.props).dbPort,
               .username = std::get<MasterCtxProps>(ctx.props).dbUsername,
               .password = std::get<MasterCtxProps>(ctx.props).dbPassword,
               .database = std::get<MasterCtxProps>(ctx.props).dbName,
           }) {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<MasterCtxProps>(ctx.props)};
}

int rtype::server::Master::Master::Run() {
  api_.Join();
  return EXIT_SUCCESS;
}
