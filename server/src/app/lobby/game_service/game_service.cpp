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
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
  InitEntites();
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run() {
  Initialize();

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

void GameService::InitEntites() {
  auto ent1 = registry_->SpawnEntity();
  auto ent2 = registry_->SpawnEntity();

  registry_->AddComponent<core::components::Position>(
      ent1, core::components::Position{core::types::Vector3f{0, 0, 0}});
  registry_->AddComponent<core::components::Position>(
      ent2, core::components::Position{core::types::Vector3f{2, 0, 0}});
  registry_->AddComponent<physics::components::Rigidbody2D>(ent1,
                                                            physics::components::Rigidbody2D{});
  registry_->AddComponent<physics::components::Rigidbody2D>(
      ent2, physics::components::Rigidbody2D{core::types::Vector2f::left()});
  registry_->AddComponent<physics::components::BoxCollider2D>(
      ent1, physics::components::BoxCollider2D{core::types::Vector2f(1, 1)});
  registry_->AddComponent<physics::components::BoxCollider2D>(
      ent2, physics::components::BoxCollider2D{core::types::Vector2f(1, 1)});
}
