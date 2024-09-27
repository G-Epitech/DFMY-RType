/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.cpp
*/

#include "options_handler_allocator.hpp"

#include <filesystem>
#include <iostream>

#include "server/src/env/env.hpp"

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
  Env env;
  const auto &envPath = mVariablesMap["env"].as<std::string>();
  env.Load(envPath);
}

void OptionsHandlerAllocator::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "env", po::value<std::string>()->required(), "allocator server env file");
}

void OptionsHandlerAllocator::LoadEnvFile() {}
