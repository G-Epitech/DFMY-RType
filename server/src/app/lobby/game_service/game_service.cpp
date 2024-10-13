/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <iostream>
#include <thread>

#include "factories/player_factory.hpp"
#include "factories/projectile_factory.hpp"

using namespace rtype::server::game;

GameService::GameService(const size_t& tick_rate) : ticksManager_{tick_rate}, registry_() {}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
  PlayerFactory::CreatePlayer(registry_, core::types::Vector3f(0, 0, 0), {5, 5});
  ProjectileFactory::CreateProjectile(registry_, core::types::Vector3f(7, 0, 0), {5, 5});
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run() {
  Initialize();
  std::cout << "GameService is running" << std::endl;

  while (gameRunning_) {
    ticksManager_.Update();
    ExecuteGameLogic();
    ticksManager_.WaitUntilNextTick();
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() const {
  registry_->RunSystems();
}
