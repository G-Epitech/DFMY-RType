/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.cpp
*/

#include "options.hpp"

#include <iostream>

using namespace rtype::server::cli;

Options::Options() : mVariablesMap(), mDescription("Allowed options") {
  Setup();
}

void Options::Parse(int ac, char **av) {
  po::positional_options_description p;
  p.add("type", 1);
  po::store(po::command_line_parser(ac, av).options(mDescription).positional(p).run(),
            mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
    return;
  }
  try {
    po::notify(mVariablesMap);
    if (mVariablesMap.count("type")) {
      std::cout << mVariablesMap["type"].as<ServerType>() << ".\n";
    }
  } catch (const po::error &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
}

void Options::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "type", po::value<ServerType>()->required(), "type of the server (main or lobby)");
}

void Options::AssignOptionsHandler(rtype::server::ServerType serverType) noexcept {
  switch (serverType) {
    case kLobby:
      mOptionHandler = std::make_unique<OptionsHandlerLobby>();
    default:
      mOptionHandler = std::make_unique<OptionsHandlerAllocator>();
  };
}
