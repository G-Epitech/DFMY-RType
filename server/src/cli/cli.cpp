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
  std::cout << "\tlobby   \tgame server that's created by the master for auto-scaling\n";
}

CliHandler Cli::GetHandler(const std::string &typeArg) {
  const auto &type = StringToServerType(typeArg);

  switch (type) {
    case kLobby:
      return std::make_unique<CliHandlerLobby>();
    case kMaster:
      return std::make_unique<CliHandlerMaster>();
    default:
      throw std::invalid_argument("Unkown server type: '" + typeArg + "'");
  }
}
