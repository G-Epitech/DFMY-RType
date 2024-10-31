/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "app/room/filepaths.hpp"
#include "app/room/game_service/archetype_keys.hpp"
#include "app/room/game_service/scripts/scripts_registry.hpp"
#include "libs/zygarde/src/scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"
#include "state_broadcaster/state_broadcaster.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, registry_(), enemyManager_(), logger_("game-service") {
  archetypeManager_ = std::make_shared<zygarde::core::archetypes::ArchetypeManager>();
}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::Create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime(),
                                             archetypeManager_);
}

void GameService::Initialize() {
  std::vector<std::string> archetypeDirs = {kDirectoryPlayerArchetypes, kDirectoryEnemyArchetypes,
                                            kDirectoryProjectileArchetypes};
  scripts::ScriptsRegistry scriptsRegistry;

  ticksManager_.Initialize();
  archetypeManager_->LoadArchetypes(archetypeDirs, scriptsRegistry.GetScripts());
  RegistrySetup();
}

int GameService::Run(std::shared_ptr<Room> api) {
  this->api_ = std::move(api);

  try {
    Initialize();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
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
  archetypeManager_->ExecuteScheduledInvocations(registry_);
  if (!players_.empty()) {
    enemyManager_.Update(ticksManager_.DeltaTime(), registry_, archetypeManager_);
  }
  registry_->RunSystems();
  CheckDeadPlayers();
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
  try {
    const auto packet = packetBuilder_.Build<payload::Movement>(data.bitset);
    auto &[entityId, direction] = packet->GetPayload();

    if (const auto player = players_.find(player_id); player != players_.end()) {
      const auto &playerEntity = player->second;
      auto scriptPool = registry_->GetComponent<scripting::components::ScriptPool>(playerEntity);
      if (!scriptPool) {
        return;
      }
      auto playerScript = (*scriptPool)->GetScript<scripts::PlayerScript>();
      if (playerScript) {
        playerScript->SetMovementDirection({direction.x, direction.y});
      }
    }
  } catch (const std::exception &e) {
    logger_.Error("Error while handling player move: " + std::string(e.what()), "❌");
    return;
  }
}

void GameService::HandlePlayerShootMessage(const std::uint64_t &player_id,
                                           const abra::server::ClientUDPMessage &) {
  const auto player = players_.find(player_id);
  if (player != players_.end()) {
    const auto &playerEntity = player->second;
    if (!registry_->HasEntityAtIndex(playerEntity.operator std::size_t())) {
      return;
    }
    auto scriptPool = registry_->GetComponent<scripting::components::ScriptPool>(playerEntity);
    if (!scriptPool.has_value() || !scriptPool.value()) {
      return;
    }
    auto playerScript = (*scriptPool)->GetScript<scripts::PlayerScript>();
    if (playerScript) {
      playerScript->Shoot();
    } else {
      logger_.Error("Player script not found");
    }
  }
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = archetypeManager_->InvokeArchetype(registry_, tools::kArchetypePlayerPhoton);
  auto position = registry_->GetComponent<core::components::Position>(player);

  if (!position.has_value() || !position.value()) {
    return;
  }

  (*position)->point = core::types::Vector3f(487.0f, 100.0f + (100.0f * player_id), 0);
  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

void GameService::CheckDeadPlayers() {
  std::vector<zygarde::Entity> entitiesToKill = registry_->GetEntitiesToKill();

  for (auto it = players_.begin(); it != players_.end();) {
    if (std::find(entitiesToKill.begin(), entitiesToKill.end(), it->second) !=
        entitiesToKill.end()) {
      logger_.Info("Player " + std::to_string(it->first) + " died", "💀");
      it = players_.erase(it);
    } else {
      ++it;
    }
  }
}
