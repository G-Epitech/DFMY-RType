/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <iostream>
#include <thread>

using namespace rtype::server::game;

GameService::GameService(const size_t& tick_rate) : ticksManager_{tick_rate}, registry_() {}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::create();
  std::cout << "Registry created" << std::endl;
  utils::RegistryHelper::RegisterBaseComponents(registry_.get());
  utils::RegistryHelper::RegisterBaseSystems(registry_.get(), ticksManager_.DeltaTime());
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

void GameService::Run() {
  Initialize();

  while (gameRunning_) {
    ticksManager_.Update();
    ExecuteGameLogic();
    ticksManager_.WaitUntilNextTick();
  }
}

void GameService::ExecuteGameLogic() const {
  std::cout << "Game logic executed" << gameRunning_ << std::endl;
}
