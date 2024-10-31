/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.cpp
*/

#include "server/src/app/node/node.hpp"

#include <boost/process.hpp>
#include <iostream>

rtype::server::Node::Node(const BaseContext &ctx)
    : ctx_(),
      api_(ctx.name, std::get<NodeCtxProps>(ctx.props).masterToken,
           std::get<NodeCtxProps>(ctx.props).maxRooms, std::get<NodeCtxProps>(ctx.props).ip,
           ctx.port) {
  ctx_ = {.name = ctx.name,
          .port = ctx.port,
          .type = ctx.type,
          .props = std::get<NodeCtxProps>(ctx.props)};
}

rtype::server::Node::~Node() {
  for (auto &child : childrens_) {
    child.terminate();
    child.wait();
  }
}

int rtype::server::Node::Node::Run() {
  api_.Start(
      [this](std::uint64_t id, std::size_t maxPlayers, std::size_t difficulty, unsigned int port) {
        return this->CreateNewRoom(id, maxPlayers, difficulty, port);
      });
  api_.Join();
  return EXIT_SUCCESS;
}

bool rtype::server::Node::CreateNewRoom(std::uint64_t roomId, std::size_t maxPlayers,
                                        std::size_t difficulty, unsigned int port) {
  boost::process::child roomProcess(
      ctx_.props.binaryPath, "room", "--name", ctx_.name, "--port", std::to_string(port), "--ticks",
      std::to_string(60), "--token", ctx_.props.token, "--id", std::to_string(roomId),
      "--maxPlayers", std::to_string(maxPlayers), "--difficulty", std::to_string(difficulty));

  this->childrens_.push_back(std::move(roomProcess));
  return roomProcess.joinable();
}
