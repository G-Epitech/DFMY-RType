/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level_manager.cpp
*/

#include "level_manager.hpp"

#include <iostream>

using namespace rtype::server::game;

void LevelManager::Initialize(
    const std::string& levels_path, const std::shared_ptr<zygarde::Registry>& registry,
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager) {
  levels_ = LevelLoader().Run(levels_path);
  enemySpawner_.Initialize(archetype_manager, registry);
}

void LevelManager::SelectLevel(const std::string& level_name) {
  for (const auto& level : levels_) {
    if (level.name == level_name) {
      selectedLevel_ = level;
      return;
    }
  }
  throw std::runtime_error("Level not found");
}

void LevelManager::Update(const utils::Timer::Nanoseconds& delta_time) {
  currentWaveTime_ -= delta_time;
  UpdateSpawnCooldowns(delta_time);
  if (currentWaveTime_ <= utils::Timer::Nanoseconds{0}) {
    NextWave();
  }
}

void LevelManager::StartLevel(DifficultyData difficulty) {
  enemySpawner_.SetDifficulty(difficulty);
  BuildSpawnCooldowns();
  NextWave();
}

void LevelManager::BuildSpawnCooldowns() {
  for (const auto& wave : selectedLevel_.waves) {
    SpawnCooldowns waveCooldowns;
    auto totalWaveTime = wave.maxTime;
    for (const auto& [enemyName, enemyCount] : wave.enemies) {
      auto spawnTime = ComputeEnemySpawnCooldown(totalWaveTime, enemyCount);
      waveCooldowns[enemyName] = {spawnTime, zygarde::utils::Timer::Nanoseconds{0}};
    }
    levelSpawnCooldowns_.push_back(waveCooldowns);
  }
}

void LevelManager::NextWave() {
  currentWaveIndex_++;
  if (currentWaveIndex_ >= selectedLevel_.waves.size()) {
    return;
  }
  currentWave_ = selectedLevel_.waves[currentWaveIndex_];
  float maxTime = currentWave_.maxTime;
  currentWaveTime_ =
      std::chrono::nanoseconds(static_cast<int64_t>(maxTime * kNanosecondsPerSecond));
  ongoingSpawnCooldowns_.push_back(levelSpawnCooldowns_[currentWaveIndex_]);
}

zygarde::utils::Timer::Nanoseconds LevelManager::ComputeEnemySpawnCooldown(float wave_max_time,
                                                                           int enemy_count) {
  return zygarde::utils::Timer::Nanoseconds{static_cast<int64_t>(
      wave_max_time / static_cast<float>(enemy_count) * kNanosecondsPerSecond)};
}

void LevelManager::UpdateSpawnCooldowns(const utils::Timer::Nanoseconds& deltaTime) {
  for (auto& spawnCooldowns : ongoingSpawnCooldowns_) {
    stillSpawning_ = false;
    for (auto& [enemyName, spawnProps] : spawnCooldowns) {
      if (spawnProps.count >= currentWave_.enemies[enemyName]) {
        continue;
      }
      stillSpawning_ = true;
      spawnProps.currentSpawnTime += deltaTime;
      if (CanSpawnEnemy(enemyName, spawnCooldowns)) {
        spawnProps.count++;
        const auto ent = enemySpawner_.SpawnEnemy(enemyName);
        spawnedEnemies_.push_back(ent);
        spawnProps.currentSpawnTime = zygarde::utils::Timer::Nanoseconds{0};
      }
    }
  }
}

bool LevelManager::CanSpawnEnemy(const std::string& enemy_name,
                                 const LevelManager::SpawnCooldowns& waveCooldowns) {
  const auto& spawnProps = waveCooldowns.at(enemy_name);
  return spawnProps.currentSpawnTime >= spawnProps.spawnTime;
}

void LevelManager::CheckDeadEnemies(const std::list<Entity>& entities_to_kill) {
  for (auto it = spawnedEnemies_.begin(); it != spawnedEnemies_.end();) {
    if (std::find(entities_to_kill.begin(), entities_to_kill.end(), *it) !=
        entities_to_kill.end()) {
      it = spawnedEnemies_.erase(it);
    } else {
      ++it;
    }
  }
}
