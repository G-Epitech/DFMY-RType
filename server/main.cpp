/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>

#include "src/allocator/allocator.hpp"
#include "src/cli/cli.hpp"
#include "src/cli/handlers/cli_handler_interface.hpp"
#include "src/lobby/lobby.hpp"

int main(int ac, char **av) {
  rtype::server::CliResult cliResult;
  try {
    cliResult = rtype::server::Cli::Run(ac, av);
  } catch (std::exception &exception) {
    std::cerr << exception.what();
  }
  if (!cliResult.has_value()) {
    return 0;
  }
  auto ctx = cliResult.value();
  if (ctx.type == rtype::server::kAllocator) {
    rtype::server::Allocator allocator(ctx);
  } else {
    rtype::server::Lobby lobby(ctx);
  }
  return 0;
}
