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
    AssignOptionsHandler(firstArg);
    mOptionsHandler->Parse(ac - 2, av + 2);
  } catch (const po::error &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
}
void Options::Usage() noexcept {
  std::cout << "Help message\n";
}

void Options::AssignOptionsHandler(const std::string &typeArg) noexcept {
  const auto &type = StringToServerType(typeArg);

  switch (type) {
    case kLobby:
      mOptionsHandler = std::make_unique<OptionsHandlerLobby>();
      return;
    default:
      mOptionsHandler = std::make_unique<OptionsHandlerAllocator>();
      return;
  };
}
