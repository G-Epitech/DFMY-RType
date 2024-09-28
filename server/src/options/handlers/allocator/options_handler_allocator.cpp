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

void OptionsHandlerAllocator::Setup() noexcept {
  mDescription.add_options()("help", "produce help message")(
      "env", po::value<std::string>()->required(), "allocator server env file");
}

CliResult OptionsHandlerAllocator::Parse(int ac, char **av) {
  po::store(po::parse_command_line(ac, av, mDescription), mVariablesMap);

  if (mVariablesMap.count("help")) {
    std::cout << mDescription << "\n";
    return std::nullopt;
  }
  po::notify(mVariablesMap);
  return BuildCtx();
}

rtype::server::BaseContext OptionsHandlerAllocator::BuildCtx() {
  const auto &envPath = mVariablesMap["env"].as<std::string>();
  Env env(envPath);

  auto name = env.Get<std::string>("NAME");
  std::size_t port = static_cast<std::size_t>(env.Get<long>("PORT"));
  std::size_t maxGames = static_cast<std::size_t>(env.Get<long>("MAX_GAMES"));
  std::size_t ticks = static_cast<std::size_t>(env.Get<long>("TICKS"));
  AllocatorCtxProps props = AllocatorCtxProps(maxGames, ticks);

  return {name, port, kAllocator, props};
}
