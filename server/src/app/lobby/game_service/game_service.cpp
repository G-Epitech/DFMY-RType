/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "app/lobby/game_service/archetype_manager/archetype_keys.hpp"
#include "constants/tags.hpp"
#include "libs/zygarde/src/scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"
#include "state_broadcaster/state_broadcaster.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, registry_(), enemyManager_(), logger_("game-service") {
  archetypeManager_ = std::make_shared<tools::ArchetypeManager>();
}

void GameService::RegistrySetup() {
  registry_ = Registry::create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
  archetypeManager_->LoadArchetypes();
}

int GameService::Run(std::shared_ptr<Lobby> api) {
  this->api_ = std::move(api);

  Initialize();
  while (gameRunning_) {
    ticksManager_.Update();
    HandleMessages();
    ExecuteGameLogic();
    StateBroadcaster::Run(registry_, api_);
    ticksManager_.WaitUntilNextTick();
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  if (!players_.empty()) {
    enemyManager_.Update(ticksManager_.DeltaTime(), registry_, archetypeManager_);
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
  if (data.messageType == kMovement) {
    HandlePlayerMoveMessage(player_id, data);
  }
  if (data.messageType == kShoot) {
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
    auto scriptPool = registry_->GetComponent<scripting::components::ScriptPool>(playerEntity);
    auto playerScript = scriptPool->GetScript<scripts::PlayerScript>();
    if (playerScript) {
      std::cout << "Player " << player_id << " shot" << std::endl;
      playerScript->Shoot();
    } else {
      logger_.Error("Player script not found");
    }
  }
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = archetypeManager_->InvokeArchetype(registry_, tools::kArchetypeKeyPlayerPhoton);
  auto position = registry_->GetComponent<core::components::Position>(player);

  position->point = core::types::Vector3f(487.0f, 100.0f + (100.0f * player_id), 0);
  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}
