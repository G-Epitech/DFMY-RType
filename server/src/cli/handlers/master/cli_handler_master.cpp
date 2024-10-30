/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.cpp
*/

#include "cli_handler_master.hpp"

#include <filesystem>
#include <iostream>

#include "config/config.hpp"

using namespace rtype::server;

CliHandlerMaster::CliHandlerMaster() : AbstractCliHandler() {
  Setup();
}

void CliHandlerMaster::Setup() noexcept {
  optDescription_.add_options()("help", "produce help message")(
      "config", po::value<std::string>()->required(), "master server config file");
}

CliResult CliHandlerMaster::Run(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, optDescription_), variablesMap_);

  if (variablesMap_.count("help")) {
    std::cout << optDescription_ << "\n";
    return std::nullopt;
  }
  po::notify(variablesMap_);
  return BuildCtx();
}

rtype::server::BaseContext CliHandlerMaster::BuildCtx() {
  const auto &configPath = variablesMap_["config"].as<std::string>();
  Config config(configPath);

  auto name = config.Get<std::string>("NAME");
  std::size_t port = static_cast<std::size_t>(config.Get<int>("PORT"));
  auto token = config.Get<std::string>("TOKEN");
  std::size_t nodePort = static_cast<std::size_t>(config.Get<int>("NODE_PORT"));
  MasterCtxProps props = MasterCtxProps(token, nodePort);
  return {name, port, ServerType::kMaster, props};
}
