/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "app/room/filepaths.hpp"
#include "app/room/game_service/scripts/scripts_registry.hpp"
#include "network/state_broadcaster/state_broadcaster.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, registry_(), logger_("game-service") {
  archetypeManager_ = std::make_shared<zygarde::core::archetypes::ArchetypeManager>();
}

void GameService::RegistrySetup() {
  registry_ = zygarde::Registry::Create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime(),
                                             archetypeManager_);
}

void GameService::AddGameWalls() {
  archetypeManager_->InvokeArchetype(registry_, "top_wall");
  archetypeManager_->InvokeArchetype(registry_, "bottom_wall");
  archetypeManager_->InvokeArchetype(registry_, "left_wall");
  archetypeManager_->InvokeArchetype(registry_, "right_wall");
}

void GameService::LevelAndDifficultySetup() {
  difficultyLoader_.Run(kDirectoryDifficulties);
  auto difficultyData =
      difficultyLoader_.GetDifficultyByType(rtype::sdk::game::types::Difficulty::kEasy);
  playerSpawner_.Initialize(archetypeManager_, registry_);
  playerSpawner_.SetDifficulty(difficultyData);
  levelManager_.Initialize(kDirectoryLevels, registry_, archetypeManager_);
  levelManager_.SelectLevel("The Den");
  levelManager_.StartLevel(difficultyData);
}

void GameService::Initialize() {
  scripts::ScriptsRegistry scriptsRegistry;

  ticksManager_.Initialize();
  archetypeManager_->LoadArchetypes(kDirectoryArchetypes, scriptsRegistry.GetScripts());
  RegistrySetup();
  AddGameWalls();
  LevelAndDifficultySetup();
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
    messageHandler_.Run(registry_, api_, players_);
    ExecuteGameLogic();
    network::StateBroadcaster::Run(registry_, api_);
    ticksManager_.WaitUntilNextTick();
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  archetypeManager_->ExecuteScheduledInvocations(registry_);
  if (!players_.empty()) {
    levelManager_.Update(ticksManager_.DeltaTime());
  }
  registry_->RunSystems();
  CheckDeadPlayers();
  registry_->CleanupDestroyedEntities();
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = playerSpawner_.SpawnPlayer(player_id);
  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

void GameService::CheckDeadPlayers() {
  auto entitiesToKill = registry_->GetEntitiesToKill();

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
