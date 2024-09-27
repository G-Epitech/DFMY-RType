/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.cpp
*/

#include "options_handler_lobby.hpp"

#include <iostream>

using namespace rtype::server::cli;

OptionsHandlerLobby::OptionsHandlerLobby() : OptionsHandlerAbstract() {
  Setup();
}

void OptionsHandlerLobby::Parse(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, mDescription), mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
    return;
  }
  po::notify(mVariablesMap);
}

void OptionsHandlerLobby::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "ticks", po::value<std::size_t>()->default_value(kDefaultTicks),
      "number of ticks for the game")("name", po::value<std::string>()->default_value(""),
                                      "name of the lobby");
}
