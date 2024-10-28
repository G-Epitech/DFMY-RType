/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "constants/tags.hpp"
#include "factories/player_factory.hpp"
#include "libs/zygarde/src/scripting/components/script/script.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, registry_(), enemyManager_(), logger_("game-service") {}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::Create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run(std::shared_ptr<Room> api) {
  this->api_ = std::move(api);

  Initialize();

  while (gameRunning_) {
    ticksManager_.Update();
    HandleMessages();
    ExecuteGameLogic();
    BroadcastEntityStates();
    ticksManager_.WaitUntilNextTick();
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  if (!players_.empty()) {
    enemyManager_.Update(ticksManager_.DeltaTime(), registry_);
  }
  registry_->RunSystems();
  registry_->CleanupDestroyedEntities();
}

void GameService::HandleMessages() {
  auto messages = api_->ExtractQueue();

  while (!messages.empty()) {
    auto &[playerId, data] = messages.front();
    HandlePlayerMessage(playerId, data);
    messages.pop();
  }
}

void GameService::HandlePlayerMessage(const std::uint64_t &player_id,
                                      const abra::server::ClientUDPMessage &data) {
  if (data.messageType == ClientToRoomMsgType::kMsgTypeCTRPlayerMove) {
    HandlePlayerMoveMessage(player_id, data);
  }
  if (data.messageType == ClientToRoomMsgType::kMsgTypeCTRPlayerShoot) {
    HandlePlayerShootMessage(player_id, data);
  }
}

void GameService::HandlePlayerMoveMessage(const std::uint64_t &player_id,
                                          const abra::server::ClientUDPMessage &data) {
  const auto packet = packetBuilder_.Build<payload::Movement>(data.bitset);
  auto &[entityId, direction] = packet->GetPayload();

  if (const auto player = players_.find(player_id); player != players_.end()) {
    const auto &playerEntity = player->second;
    const auto rigidBody = registry_->GetComponent<physics::components::Rigidbody2D>(playerEntity);
    if (!rigidBody) {
      return;
    }

    const core::types::Vector2f newDir = {direction.x, direction.y};
    rigidBody->SetVelocity(newDir * 200);
  }

  logger_.Info("Player " + std::to_string(player_id) + " moved", "🏃‍");
}

void GameService::HandlePlayerShootMessage(const std::uint64_t &player_id,
                                           const abra::server::ClientUDPMessage &data) {
  auto packet = packetBuilder_.Build<payload::Shoot>(data.bitset);
  const auto player = players_.find(player_id);
  if (player != players_.end()) {
    const auto &playerEntity = player->second;
    const auto script = registry_->GetComponent<scripting::components::Script>(playerEntity);
    script->SetValue("shoot", true);
  }
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = PlayerFactory::CreatePlayer(
      registry_, core::types::Vector3f(487.0f, 100.0f + (100.0f * player_id), 0), {96, 48});

  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

void GameService::BroadcastEntityStates() const {
  std::unique_ptr<EntityStates> entityStates = std::make_unique<EntityStates>();

  GatherEntityStates(entityStates);
  SendStates(entityStates);
}

void GameService::GatherEntityStates(const std::unique_ptr<EntityStates> &states) const {
  const auto components = registry_->GetComponents<core::components::Position>();
  std::size_t i = 0;

  for (auto &component : *components) {
    if (!registry_->HasEntityAtIndex(i) || !component.has_value()) {
      i++;
      continue;
    }

    const auto val = component.value();
    auto ent = registry_->EntityFromIndex(i);
    const sdk::game::utils::types::vector_2f vec = {val.point.x, val.point.y};
    const auto tags = registry_->GetComponent<core::components::Tags>(ent);

    if (*tags == sdk::game::constants::kPlayerTag) {
      payload::PlayerState state = {static_cast<std::size_t>(ent), vec, 100};
      states->playerStates.push_back(state);
    }
    if (*tags == sdk::game::constants::kEnemyTag) {
      payload::EnemyState state = {static_cast<std::size_t>(ent), vec,
                                   sdk::game::types::EnemyType::kPata, 100};
      states->enemyStates.push_back(state);
    }
    if (*tags == sdk::game::constants::kPlayerBulletTag) {
      payload::BulletState state = {static_cast<std::size_t>(ent), vec,
                                    sdk::game::types::ProjectileType::kPlayerCommon};
      states->bulletStates.push_back(state);
    }
    if (*tags == sdk::game::constants::kEnemyBulletTag) {
      payload::BulletState state = {static_cast<std::size_t>(ent), vec,
                                    sdk::game::types::ProjectileType::kEnemyCommon};
      states->bulletStates.push_back(state);
    }
    i++;
  }
}

void GameService::SendStates(const std::unique_ptr<EntityStates> &states) const {
  if (!states->playerStates.empty()) {
    this->api_->SendPlayersState(states->playerStates);
  }
  if (!states->enemyStates.empty()) {
    this->api_->SendEnemiesState(states->enemyStates);
  }
  if (!states->bulletStates.empty()) {
    this->api_->SendBulletsState(states->bulletStates);
  }
}
