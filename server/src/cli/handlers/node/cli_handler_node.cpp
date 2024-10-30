/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.cpp
*/

#include "cli_handler_node.hpp"

#include <filesystem>
#include <iostream>

#include "config/config.hpp"

using namespace rtype::server;

CliHandlerNode::CliHandlerNode() : AbstractCliHandler() {
  Setup();
}

void CliHandlerNode::Setup() noexcept {
  optDescription_.add_options()("help", "produce help message")(
      "config", po::value<std::string>()->required(), "node server config file");
}

CliResult CliHandlerNode::Run(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, optDescription_), variablesMap_);

  if (variablesMap_.count("help")) {
    std::cout << optDescription_ << "\n";
    return std::nullopt;
  }
  po::notify(variablesMap_);
  return BuildCtx();
}

rtype::server::BaseContext CliHandlerNode::BuildCtx() {
  const auto &configPath = variablesMap_["config"].as<std::string>();
  Config config(configPath);

  auto name = config.Get<std::string>("NAME");
  std::size_t port = static_cast<std::size_t>(config.Get<int>("PORT"));
  std::size_t maxRooms = static_cast<std::size_t>(config.Get<int>("MAX_ROOMS"));
  auto token = config.Get<std::string>("TOKEN");
  auto masterToken = config.Get<std::string>("MASTER_TOKEN");
  auto binaryPath = config.Get<std::string>("BINARY_PATH");
  auto ip = config.Get<std::string>("IP");

  NodeCtxProps props = NodeCtxProps(maxRooms, token, masterToken, binaryPath, ip);
  return {name, port, ServerType::kNode, props};
}
