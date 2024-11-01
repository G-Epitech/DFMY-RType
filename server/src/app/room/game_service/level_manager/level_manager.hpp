/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level_manager.hpp
*/

#pragma once

#include "loader/level_loader.hpp"
#include "registry.hpp"
#include "types/difficulty.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class LevelManager {
 public:
  LevelManager() = default;
  ~LevelManager() = default;

 public:
  void Initialize(
      const std::string& levelsPath, const std::shared_ptr<zygarde::Registry>& registry,
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager);

  [[nodiscard]] inline std::vector<Level> GetLevels() const { return levels_; }

  void SelectLevel(const std::string& level_name);

  void StartLevel(const Difficulty &difficulty);

  void UpdateTime(const zygarde::utils::Timer::Nanoseconds& deltaTime);

  [[nodiscard]] inline bool LevelIsFinished() const noexcept {
    return currentWaveIndex_ >= selectedLevel_.waves.size();
  }

 private:
  void BuildSpawnCooldowns();

  void SpawnEnemy(const std::string& enemyName);

  void CheckEnemyDeath();

  void NextWave();

 private:
  using SpawnCooldowns = std::map<std::string, zygarde::utils::Timer::Nanoseconds>;

 private:
  Level selectedLevel_;
  std::vector<Level> levels_;
  std::size_t currentWaveIndex_ = 0;
  zygarde::utils::Timer::Nanoseconds currentWaveTime_;
  std::vector<SpawnCooldowns> spawnCooldowns_;
  std::vector<zygarde::Entity> currentlySpawnedEnemies_;
  std::shared_ptr<zygarde::Registry> registry_;
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;
  Difficulty difficulty_;
};
}  // namespace rtype::server::game
