/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** runner.cpp
*/

#include "runner.hpp"

#include <iostream>

#include "src/apps/director/director.hpp"
#include "src/apps/lobby/lobby.hpp"
#include "src/cli/cli.hpp"

using namespace rtype::server;

int Runner::StartApp(int ac, char **av) {
  rtype::server::CliResult cliResult;

  try {
    cliResult = rtype::server::Cli::Run(ac, av);
    if (!cliResult.has_value()) {
      return EXIT_SUCCESS;
    }
  } catch (std::exception &exception) {
    std::cerr << "CLI Error: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  const auto &server = InitializeServer(cliResult);
  return server->Run();
}

std::unique_ptr<IServer> Runner::InitializeServer(CliResult cliResult) {
  const auto &ctx = cliResult.value();

  if (ctx.type == rtype::server::kDirector) {
    return std::make_unique<rtype::server::Director>(ctx);
  }
  return std::make_unique<rtype::server::Lobby>(ctx);
}
