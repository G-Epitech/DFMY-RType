/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <iostream>
#include <thread>
#include <utility>

#include "factories/enemy_factory.hpp"
#include "factories/player_factory.hpp"
#include "factories/projectile_factory.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate},
      registry_(),
      enemyManager_(),
      logger_("game-service"),
      lobbyId_(0) {}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
  PlayerFactory::CreatePlayer(registry_, core::types::Vector3f(0, 0, 0), {5, 5});
  EnemyFactory::CreateEnemy(registry_, core::types::Vector3f(15, 0, 0),
                            sdk::game::types::EnemyType::kPata);
  ProjectileFactory::CreateProjectile(registry_, core::types::Vector3f(5, 0, 0), {5, 5},
                                      sdk::game::types::GameEntityType::kPlayer);
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run(uint64_t lobbyId, std::shared_ptr<rtype::sdk::game::api::Server> api) {
  this->lobbyId_ = lobbyId;
  this->api_ = std::move(api);

  Initialize();

  while (gameRunning_) {
    ticksManager_.Update();

    HandleMessages();
    ExecuteGameLogic();

    ticksManager_.WaitUntilNextTick();
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  enemyManager_.Update(ticksManager_.DeltaTime(), registry_);
  registry_->RunSystems();
  registry_->CleanupDestroyedEntities();
}

void GameService::HandleMessages() {
  auto messages = api_->ExtractLobbyQueue(lobbyId_);

  while (!messages.empty()) {
    auto &message = messages.front();
    auto playerId = message.first;
    auto &data = message.second;

    if (data.messageType == MessageClientType::kMovement) {
      auto packet = packetBuilder_.Build<payload::Movement>(data.bitset);
      auto move = packet->GetPayload();

      auto player = players_.find(playerId);
      if (player != players_.end()) {
        auto &playerEntity = player->second;
        auto rigidBody =
            registry_->GetComponent<zygarde::physics::components::Rigidbody2D>(playerEntity);

        zygarde::core::types::Vector2f direction = {move.direction.x, move.direction.y};
        rigidBody->SetVelocity(direction * 2);
      }

      logger_.Info("Player " + std::to_string(playerId) + " moved", "🏃‍♂️");
    }
    if (data.messageType == MessageClientType::kShoot) {
      auto packet = packetBuilder_.Build<payload::Shoot>(data.bitset);
      auto move = packet->GetPayload();

      auto player = players_.find(playerId);
      if (player != players_.end()) {
        auto &playerEntity = player->second;
        auto position = registry_->GetComponent<zygarde::core::components::Position>(playerEntity);

        ProjectileFactory::CreateProjectile(registry_, position->point, {10, 10},
                                            sdk::game::types::GameEntityType::kPlayer);
      }
    }
    messages.pop();
  }
}

void GameService::NewPlayer(std::uint64_t playerId) {
  Entity player = PlayerFactory::CreatePlayer(registry_, core::types::Vector3f(0, 0, 0), {96, 48});

  players_.insert({playerId, player});
  logger_.Info("Player " + std::to_string(playerId) + " joined the game", "❇️");
}
