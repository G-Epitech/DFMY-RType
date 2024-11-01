/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level_manager.cpp
*/

#include "level_manager.hpp"

using namespace rtype::server::game;

void LevelManager::Initialize(
    const std::string& levelsPath, const std::shared_ptr<zygarde::Registry>& registry,
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager) {
  levels_ = LevelLoader().Run(levelsPath);
  archetypeManager_ = archetypeManager;
  registry_ = registry;
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

void LevelManager::UpdateTime(const utils::Timer::Nanoseconds& deltaTime) {
  currentWaveTime_ -= deltaTime;
}

void LevelManager::StartLevel(const Difficulty& difficulty) {
  currentWaveIndex_ = 0;
  currentWaveTime_ = zygarde::utils::Timer::Nanoseconds{0};
  difficulty_ = difficulty;
}
