/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app.cpp
*/

#include "app.hpp"

#include <iostream>

#include "app/master/master.hpp"
#include "app/node/node.hpp"
#include "app/room/room.hpp"
#include "cli/cli.hpp"

using namespace rtype::server;

int App::Run(int ac, char **av) {
  const int status = ParseArguments(ac, av);

  if (!cliResult_.has_value()) {
    return status;
  }
  try {
    InitializeServerInstance();
  } catch (std::exception &exception) {
    std::cerr << "Server Error: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  return server_->Run();
}

void App::InitializeServerInstance() {
  const auto &ctx = cliResult_.value();

  switch (ctx.type) {
    case ServerType::kMaster:
      server_ = std::make_unique<Master>(ctx);
      break;
    case ServerType::kNode:
      server_ = std::make_unique<Node>(ctx);
      break;
    case ServerType::kRoom:
      server_ = std::make_unique<Room>(ctx);
      break;
    default:
      throw std::runtime_error("Invalid server type");
  }
}

int App::ParseArguments(int ac, char **av) {
  try {
    cliResult_ = Cli::Run(ac, av);
  } catch (std::exception &exception) {
    std::cerr << "CLI Error: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
