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
    const std::string& levels_path, const std::string& difficulties_path,
    const std::shared_ptr<zygarde::Registry>& registry,
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager) {
  difficultyLoader_.Run(difficulties_path);
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

void LevelManager::Update(const utils::Timer::Nanoseconds& deltaTime) {
  currentWaveTime_ -= deltaTime;
  UpdateSpawnCooldowns(deltaTime);
  if (currentWaveTime_ <= utils::Timer::Nanoseconds{0}) {
    NextWave();
  }
}

void LevelManager::StartLevel(rtype::sdk::game::types::Difficulty difficulty) {
  auto difficultyData = difficultyLoader_.GetDifficultyByType(difficulty);
  enemySpawner_.SetDifficulty(difficultyData);
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
    spawnCooldowns_.push_back(waveCooldowns);
  }
}

void LevelManager::NextWave() {
  currentWaveIndex_++;
  if (currentWaveIndex_ >= selectedLevel_.waves.size()) {
    return;
  }
  currentWave_ = selectedLevel_.waves[currentWaveIndex_];
  float maxTime = currentWave_.maxTime;
  currentWaveTime_ = std::chrono::nanoseconds(static_cast<int64_t>(maxTime * 1'000'000'000.0));
}

zygarde::utils::Timer::Nanoseconds LevelManager::ComputeEnemySpawnCooldown(float wave_max_time,
                                                                           int enemy_count) {
  return zygarde::utils::Timer::Nanoseconds{
      static_cast<int64_t>(wave_max_time / static_cast<float>(enemy_count) * 1'000'000'000.0)};
}

void LevelManager::UpdateSpawnCooldowns(const utils::Timer::Nanoseconds& deltaTime) {
  auto& currentWaveCooldowns = spawnCooldowns_[currentWaveIndex_];

  for (auto& [enemyName, spawnProps] : currentWaveCooldowns) {
    std::cout << currentWaveIndex_ << std::endl;
    std::cout << "Enemy " << enemyName << " has " << spawnProps.count << " spawned" << std::endl;
    std::cout << "Enemy Name: " << enemyName << " Spawn Time: " << spawnProps.spawnTime.count()
              << " Current Spawn Time: " << spawnProps.currentSpawnTime.count() << std::endl;
    spawnProps.currentSpawnTime += deltaTime;
    if (CanSpawnEnemy(enemyName, currentWaveCooldowns)) {
      spawnProps.count++;
      enemySpawner_.SpawnEnemy(enemyName);
      spawnProps.currentSpawnTime = zygarde::utils::Timer::Nanoseconds{0};
    }
  }
}

bool LevelManager::CanSpawnEnemy(const std::string& enemy_name,
                                 LevelManager::SpawnCooldowns& waveCooldowns) {
  auto& spawnProps = waveCooldowns[enemy_name];
  return spawnProps.currentSpawnTime >= spawnProps.spawnTime &&
         spawnProps.count < currentWave_.enemies[enemy_name];
}
