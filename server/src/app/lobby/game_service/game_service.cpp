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
#include "libs/game/src/utils/types/vector/vector_2f.hpp"

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
    SendStates();

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

        if (!rigidBody) {
          continue;
        }

        zygarde::core::types::Vector2f direction = {move.direction.x, move.direction.y};
        rigidBody->SetVelocity(direction * 200);
      }

      logger_.Info("Player " + std::to_string(playerId) + " moved", "🏃‍");
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
  Entity player = PlayerFactory::CreatePlayer(
      registry_, core::types::Vector3f(487.0f, 100.0f + (100.0f * playerId), 0), {96, 48});

  players_.insert({playerId, player});
  logger_.Info("Player " + std::to_string(playerId) + " joined the game", "❇️");
}

void GameService::SendStates() {
  auto components = registry_->GetComponents<zygarde::core::components::Position>();
  std::size_t i = 0;
  std::vector<rtype::sdk::game::api::payload::PlayerState> states;
  std::vector<rtype::sdk::game::api::payload::EnemyState> enemyStates;
  std::vector<rtype::sdk::game::api::payload::BulletState> bulletStates;
  for (auto &component : *components) {
    if (!component.has_value()) {
      continue;
    }
    auto val = component.value();
    if (!registry_->HasEntityAtIndex(i)) {
      break;
    }
    auto ent = registry_->EntityFromIndex(i);
    rtype::sdk::game::utils::types::vector_2f vec = {val.point.x, val.point.y};
    std::cout << "Entity: " << static_cast<std::size_t>(ent) << " Position: " << vec.x << " "
              << vec.y << std::endl;
    auto tags = registry_->GetComponent<zygarde::core::components::Tags>(ent);
    if (*tags == rtype::sdk::game::constants::kPlayerTag) {
      rtype::sdk::game::api::payload::PlayerState state = {static_cast<std::size_t>(ent), vec, 100};
      states.push_back(state);
    }
    if (*tags == rtype::sdk::game::constants::kEnemyTag) {
      rtype::sdk::game::api::payload::EnemyState state = {
          static_cast<std::size_t>(ent), vec, rtype::sdk::game::types::EnemyType::kPata, 100};
      enemyStates.push_back(state);
    }
    if (*tags == rtype::sdk::game::constants::kPlayerBulletTag ||
        *tags == rtype::sdk::game::constants::kEnemyBulletTag) {
      rtype::sdk::game::api::payload::BulletState state = {static_cast<std::size_t>(ent), vec};
      bulletStates.push_back(state);
    }
    i++;
  }

  if (!states.empty())
    this->api_->SendPlayersState(lobbyId_, states);
  if (!enemyStates.empty())
    this->api_->SendEnemiesState(lobbyId_, enemyStates);
  if (!bulletStates.empty())
    this->api_->SendBulletsState(lobbyId_, bulletStates);
}
