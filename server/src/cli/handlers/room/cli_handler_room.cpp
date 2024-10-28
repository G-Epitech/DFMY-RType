/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.cpp
*/

#include "cli_handler_room.hpp"

#include <iostream>

using namespace rtype::server;

CliHandlerRoom::CliHandlerRoom() : AbstractCliHandler() {
  Setup();
}

void CliHandlerRoom::Setup() noexcept {
  optDescription_.add_options()("help", "produce help message")(
      "name", po::value<std::string>()->default_value(kDefaultName), "name of the lobby")(
      "port", po::value<std::size_t>()->required(), "port of the server")(
      "ticks", po::value<std::size_t>()->default_value(kDefaultTicks),
      "number of ticks for the game")("token", po::value<std::string>()->required(),
                                      "token for the node auth")(
      "id", po::value<std::size_t>()->required(), "id of the room");
}

CliResult CliHandlerRoom::Run(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, optDescription_), variablesMap_);

  if (variablesMap_.count("help")) {
    std::cout << optDescription_ << "\n";
    return std::nullopt;
  }
  po::notify(variablesMap_);
  return BuildCtx();
}

rtype::server::BaseContext CliHandlerRoom::BuildCtx() {
  std::string name = variablesMap_["name"].as<std::string>();
  std::size_t port = variablesMap_["port"].as<std::size_t>();
  std::size_t ticks = variablesMap_["ticks"].as<std::size_t>();
  std::string token = variablesMap_["token"].as<std::string>();
  std::size_t id = variablesMap_["id"].as<std::size_t>();
  auto props = RoomCtxProps(ticks, token, id);

  return {name, port, ServerType::kRoom, props};
}
