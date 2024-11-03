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
#include "libs/game/src/constants/tags.hpp"
#include "network/state_broadcaster/state_broadcaster.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate, std::size_t difficulty)
    : ticksManager_{tick_rate}, registry_(), logger_("game-service"), difficulty_(difficulty) {
  archetypeManager_ = std::make_shared<zygarde::core::archetypes::ArchetypeManager>();
  playerCounter_ = 0;
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
      difficultyLoader_.GetDifficultyByType(static_cast<sdk::game::types::Difficulty>(difficulty_));
  playerSpawner_.Initialize(archetypeManager_, registry_);
  playerSpawner_.SetDifficulty(difficultyData);
  levelManager_.Initialize(kDirectoryLevels, registry_, archetypeManager_);
  levelManager_.SelectLevel("The Den");
  levelManager_.StartLevel(difficultyData);
}

int GameService::Initialize() {
  try {
    scripts::ScriptsRegistry scriptsRegistry;

    archetypeManager_->LoadArchetypes(kDirectoryArchetypes, scriptsRegistry.GetScripts());
    RegistrySetup();
    AddGameWalls();
    LevelAndDifficultySetup();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int GameService::Run(std::shared_ptr<Room> api) {
  this->api_ = std::move(api);

  ticksManager_.Initialize();
  while (gameRunning_) {
    ticksManager_.Update();
    messageHandler_.Run(registry_, api_, players_);
    ExecuteGameLogic();
    network::StateBroadcaster::Run(registry_, api_);
    ticksManager_.WaitUntilNextTick();
    UpdateTotalGameTime();
  }
  HandleGameEnd();
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  archetypeManager_->ExecuteScheduledInvocations(registry_);
  if (!players_.empty()) {
    levelManager_.Update(ticksManager_.DeltaTime());
  }
  registry_->RunSystems();
  CheckTooFarEntities();
  CheckDeadPlayers();
  levelManager_.CheckDeadEnemies(registry_->GetEntitiesToKill());
  registry_->CleanupDestroyedEntities();
  UpdatePlayerScores();
  CheckGameEnd();
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = playerSpawner_.SpawnPlayer(player_id);
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️ ");
  players_.insert({player_id, {player, 0}});
  playerCounter_++;
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

std::size_t GameService::GetNbPlayers() const {
  return playerCounter_;
}

void GameService::CheckDeadPlayers() {
  auto entitiesToKill = registry_->GetEntitiesToKill();

  for (auto it = players_.begin(); it != players_.end();) {
    if (std::find(entitiesToKill.begin(), entitiesToKill.end(), it->second.entity) !=
        entitiesToKill.end()) {
      logger_.Info("Player " + std::to_string(it->first) + " died", "💀");
      deadPlayers_.emplace_back(it->first, it->second);
      it = players_.erase(it);
    } else {
      ++it;
    }
  }
}

void GameService::UpdatePlayerScores() {
  for (auto &player : players_) {
    const auto &entity = player.second.entity;
    const auto scriptPool = registry_->GetComponent<scripting::components::ScriptPool>(entity);
    if (!scriptPool.has_value() || !scriptPool.value()) {
      continue;
    }
    const auto playerScript = scriptPool.value()->GetScript<scripts::PlayerScript>();
    player.second.score = playerScript->GetScore();
  }
}

void GameService::HandleGameEnd() {
  if (win_) {
    logger_.Info("Game ended, players won", "🎉");
  } else {
    logger_.Info("Game ended, players lost", "💥");
  }
  const auto totalScore = ComputeTotalScore();
  if (totalScore == 0) {
    win_ = false;
  }
  logger_.Info("Total score: " + std::to_string(totalScore), "🏆");
  this->api_->EndGame(totalScore, totalGameTime_, win_);
}

void GameService::CheckGameEnd() {
  if (players_.empty() && !deadPlayers_.empty()) {
    gameRunning_ = false;
  }
  if (levelManager_.LevelIsFinished()) {
    win_ = true;
    gameRunning_ = false;
  }
}

void GameService::UpdateTotalGameTime() {
  totalGameTime_ +=
      std::chrono::duration_cast<std::chrono::seconds>(ticksManager_.DeltaTime()).count();
}

unsigned int GameService::ComputeTotalScore() const {
  unsigned int totalScore = 0;

  for (const auto &player : players_) {
    totalScore += player.second.score;
  }
  for (const auto &deadPlayer : deadPlayers_) {
    totalScore += deadPlayer.second.score;
  }
  if (scorePenalty_ > totalScore) {
    return 0;
  }
  totalScore -= scorePenalty_;
  return totalScore;
}

void GameService::CheckTooFarEntities() {
  const auto entities = registry_->GetEntities();
  std::cout << "Entities size: " << entities.size() << std::endl;
  for (const auto &entity : entities) {
    if (!entity) {
      continue;
    }
    const auto &entity_value = entity.value();
    const auto position = registry_->GetComponent<core::components::Position>(entity_value);
    if (!position.has_value() || !position.value()) {
      continue;
    }
    const auto point = position.value()->point;
    if (point.x < -100 || point.x > 2100 || point.y < -100 || point.y > 1200) {
      registry_->DestroyEntity(entity_value);
      auto tagComponent = registry_->GetComponent<Tags>(entity_value);
      if (!tagComponent.has_value() || !tagComponent.value()) {
        continue;
      }
      if ((*tagComponent.value()) & rtype::sdk::game::constants::kEnemyTag) {
        scorePenalty_ += 100;
      }
    }
  }
}
