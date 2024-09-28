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
  try {
    const auto &optionsHandler = GetHandler(firstArg);
    return optionsHandler->Run(ac, av);
  } catch (const po::error &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
  return std::nullopt;
}

void Cli::Usage() noexcept {
  std::cout << "Help message\n";
}

CliHandler Cli::GetHandler(const std::string &typeArg) noexcept {
  const auto &type = StringToServerType(typeArg);

  switch (type) {
    case kLobby:
      return std::make_unique<CliHandlerLobby>();
    default:
      return std::make_unique<CliHandlerDirector>();
  };
}
