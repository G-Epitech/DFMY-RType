/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level_manager.hpp
*/

#pragma once

#include "enemy_spawner/enemy_spawner.hpp"
#include "loader/level_loader.hpp"
#include "registry.hpp"
#include "types/difficulty.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class LevelManager final {
 public:
  LevelManager() = default;
  ~LevelManager() = default;

 public:
  void Initialize(
      const std::string& levelsPath, const std::shared_ptr<zygarde::Registry>& registry,
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager);

  [[nodiscard]] inline std::vector<Level> GetLevels() const { return levels_; }

  void SelectLevel(const std::string& level_name);

  void StartLevel(const Difficulty& difficulty);

  void Update(const utils::Timer::Nanoseconds& deltaTime);

  [[nodiscard]] inline bool LevelIsFinished() const noexcept {
    return currentWaveIndex_ >= selectedLevel_.waves.size();
  }

 private:
  struct SpawnProps {
    zygarde::utils::Timer::Nanoseconds spawnTime;
    zygarde::utils::Timer::Nanoseconds currentSpawnTime;
    int count = 0;
  };

  using SpawnCooldowns = std::map<std::string, SpawnProps>;

 private:
  void BuildSpawnCooldowns();

  static zygarde::utils::Timer::Nanoseconds ComputeEnemySpawnCooldown(float wave_max_time,
                                                                      int enemy_count);

  void UpdateSpawnCooldowns(const zygarde::utils::Timer::Nanoseconds& deltaTime);

  bool CanSpawnEnemy(const std::string& enemy_name, SpawnCooldowns& waveCooldowns);

  void SpawnEnemy(const std::string& enemy_name);

  void NextWave();

 private:
  Level selectedLevel_;
  std::vector<Level> levels_;

  std::size_t currentWaveIndex_ = -1;
  zygarde::utils::Timer::Nanoseconds currentWaveTime_{};
  Wave currentWave_;

  std::vector<SpawnCooldowns> spawnCooldowns_;
  std::vector<zygarde::Entity> currentlySpawnedEnemies_;

  EnemySpawner enemySpawner_;
};
}  // namespace rtype::server::game
