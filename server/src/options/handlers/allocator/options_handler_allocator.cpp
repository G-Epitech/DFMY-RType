/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.cpp
*/

#include "options_handler_allocator.hpp"

#include <filesystem>
#include <iostream>

using namespace rtype::server::cli;

OptionsHandlerAllocator::OptionsHandlerAllocator() : OptionsHandlerAbstract() {
  Setup();
}

void OptionsHandlerAllocator::Parse(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, mDescription), mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
    return;
  }
  po::notify(mVariablesMap);
  const auto &configPath = mVariablesMap["config"].as<std::string>();
  if (!std::filesystem::exists(configPath)) {
    throw std::runtime_error("Configuration file doesn't exist\n");
  }
  std::cout << "Config file path: " << configPath << "\n";
}

void OptionsHandlerAllocator::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "config", po::value<std::string>()->required(), "allocator server configuration file");
}
