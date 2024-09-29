/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.cpp
*/

#include "cli_handler_lobby.hpp"

#include <iostream>

using namespace rtype::server;

CliHandlerLobby::CliHandlerLobby() : CliHandlerAbstract() {
  Setup();
}

void CliHandlerLobby::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "name", po::value<std::string>()->default_value(kDefaultName), "name of the lobby")(
      "port", po::value<std::size_t>()->required(), "port of the server")(
      "ticks", po::value<std::size_t>()->default_value(kDefaultTicks),
      "number of ticks for the game");
}

CliResult CliHandlerLobby::Run(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, mDescription), mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
    return std::nullopt;
  }
  po::notify(mVariablesMap);
  return BuildCtx();
}

rtype::server::BaseContext CliHandlerLobby::BuildCtx() {
  std::string name = mVariablesMap["name"].as<std::string>();
  std::size_t port = mVariablesMap["port"].as<std::size_t>();
  std::size_t ticks = mVariablesMap["ticks"].as<std::size_t>();
  auto props = LobbyCtxProps(ticks);

  return {name, port, kLobby, props};
}
