/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.cpp
*/

#include "cli.hpp"

#include <iostream>

using namespace rtype::server;

CliResult Cli::Run(int ac, char **av) {
  if (ac < 2) {
    throw std::runtime_error("Error: Server type argument is required.");
  }

  const std::string firstArg = av[1];

  if (firstArg == "--help") {
    Usage();
    return std::nullopt;
  }
  const auto &optionsHandler = GetHandler(firstArg);
  return optionsHandler->Run(ac, av);
}

void Cli::Usage() noexcept {
  std::cout << "R-Type server CLI\n";
  std::cout << "Description: each server type has its own --help menu\n\n";
  std::cout << "Usage:\n";
  std::cout << "\t./r-type_server [server_type] ...(type specific arguments)\n";
  std::cout << "Available server types:\n";
  std::cout << "\tmaster  \tthe server that orchestrates the whole infrastructure\n";
  std::cout << "\tnode  \tnode that allow to create more rooms for players on any servers\n";
  std::cout << "\troom  \tusing by the node to create a lobby and a game\n";
}

CliHandler Cli::GetHandler(const std::string &typeArg) {
  const auto &type = StringToServerType(typeArg);

  switch (type) {
    case ServerType::kMaster:
      return std::make_unique<CliHandlerMaster>();
    case ServerType::kNode:
      return std::make_unique<CliHandlerNode>();
    case ServerType::kRoom:
      return std::make_unique<CliHandlerRoom>();
    default:
      throw std::invalid_argument("Unkown server type: '" + typeArg + "'");
  }
}
