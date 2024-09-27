/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.cpp
*/

#include "options.hpp"

#include <iostream>

using namespace rtype::server::cli;

void Options::Parse(int ac, char **av) {
  if (ac < 2) {
    std::cerr << "Error: Server type argument is required." << std::endl;
    return;
  }

  const std::string firstArg = av[1];

  if (firstArg == "--help") {
    Usage();
    return;
  }
  try {
    const auto &optionsHandler = AssignOptionsHandler(firstArg);
    optionsHandler->Parse(ac, av);
  } catch (const po::error &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
}
void Options::Usage() noexcept {
  std::cout << "Help message\n";
}

std::unique_ptr<IOptionsHandler> Options::AssignOptionsHandler(
    const std::string &typeArg) noexcept {
  const auto &type = StringToServerType(typeArg);

  switch (type) {
    case kLobby:
      return std::make_unique<OptionsHandlerLobby>();
    default:
      return std::make_unique<OptionsHandlerAllocator>();
  };
}
