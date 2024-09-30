/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app.cpp
*/

#include "app.hpp"

#include <iostream>

#include "app/lobby/lobby.hpp"
#include "app/master/master.hpp"
#include "cli/cli.hpp"

using namespace rtype::server;

int App::Run(int ac, char **av) {
  int status = Cli(ac, av);

  if (!cliResult_.has_value()) {
    return status;
  }
  InitializeServerInstance();
  return server_->Run();
}

void App::InitializeServerInstance() {
  const auto &ctx = cliResult_.value();

  if (ctx.type == kMaster) {
    server_ = std::make_unique<Master>(ctx);
  }
  if (ctx.type == kLobby) {
    server_ = std::make_unique<Lobby>(ctx);
  }
}

int App::Cli(int ac, char **av) {
  try {
    cliResult_ = Cli::Run(ac, av);
  } catch (std::exception &exception) {
    std::cerr << "CLI Error: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
