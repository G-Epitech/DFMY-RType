/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.cpp
*/

#include "options.hpp"

#include <iostream>

using namespace rtype::server;

Options::Options() : mVariablesMap(), mDescription("Allowed options") {
}

void Options::ParseArguments(int ac, char **av) {

  AddOptions();
  po::store(po::parse_command_line(ac, av, mDescription), mVariablesMap);
  po::notify(mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
  }
  if (mVariablesMap.count("type")) {
    std::cout << mVariablesMap["type"].as<ServerType>() << ".\n";
  }
}

void Options::AddOptions() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "type", po::value<ServerType>(), "The type of the server");
}
