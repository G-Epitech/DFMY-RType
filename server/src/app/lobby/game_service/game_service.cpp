/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "factories/player_factory.hpp"
#include "factories/projectile_factory.hpp"
#include "libs/game/src/utils/types/vector/vector_2f.hpp"

using namespace rtype::server::game;
using namespace sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, enemyManager_(), lobbyId_(0), logger_("game-service") {}

void GameService::RegistrySetup() {
  registry_ = Registry::create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run(const uint64_t lobby_id, std::shared_ptr<Server> api) {
  this->lobbyId_ = lobby_id;
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
        auto rigidBody = registry_->GetComponent<physics::components::Rigidbody2D>(playerEntity);

        if (!rigidBody) {
          continue;
        }

        core::types::Vector2f direction = {move.direction.x, move.direction.y};
        rigidBody->SetVelocity(direction * 200);
      }

      logger_.Info("Player " + std::to_string(playerId) + " moved", "🏃‍");
    }

    if (data.messageType == MessageClientType::kShoot) {
      auto packet = packetBuilder_.Build<payload::Shoot>(data.bitset);

      auto player = players_.find(playerId);
      if (player != players_.end()) {
        auto &playerEntity = player->second;
        auto position = registry_->GetComponent<core::components::Position>(playerEntity);

        ProjectileFactory::CreateProjectile(registry_, position->point, {10, 10},
                                            sdk::game::types::GameEntityType::kPlayer);
      }
    }
    messages.pop();
  }
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = PlayerFactory::CreatePlayer(
      registry_, core::types::Vector3f(487.0f, 100.0f + (100.0f * player_id), 0), {96, 48});

  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

void GameService::SendStates() const {
  const auto components = registry_->GetComponents<core::components::Position>();
  std::size_t i = 0;
  std::vector<payload::PlayerState> states;
  std::vector<payload::EnemyState> enemyStates;
  std::vector<payload::BulletState> bulletStates;

  for (auto &component : *components) {
    if (!component.has_value()) {
      continue;
    }
    const auto val = component.value();
    if (!registry_->HasEntityAtIndex(i)) {
      break;
    }
    auto ent = registry_->EntityFromIndex(i);
    const sdk::game::utils::types::vector_2f vec = {val.point.x, val.point.y};
    const auto tags = registry_->GetComponent<core::components::Tags>(ent);
    if (*tags == sdk::game::constants::kPlayerTag) {
      payload::PlayerState state = {static_cast<std::size_t>(ent), vec, 100};
      states.push_back(state);
    }
    if (*tags == sdk::game::constants::kEnemyTag) {
      payload::EnemyState state = {static_cast<std::size_t>(ent), vec,
                                   sdk::game::types::EnemyType::kPata, 100};
      enemyStates.push_back(state);
    }
    if (*tags == sdk::game::constants::kPlayerBulletTag ||
        *tags == sdk::game::constants::kEnemyBulletTag) {
      payload::BulletState state = {static_cast<std::size_t>(ent), vec};
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
