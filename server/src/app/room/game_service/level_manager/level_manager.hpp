/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** level_manager.hpp
*/

#pragma once

#include "enemy_spawner/enemy_spawner.hpp"
#include "level_loader/level_loader.hpp"
#include "libs/game/src/types/difficulties.hpp"
#include "registry.hpp"
#include "types/difficulty_data.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
static constexpr float kNanosecondsPerSecond = 1'000'000'000.0;
}
// namespace rtype::server::game

namespace rtype::server::game {
class LevelManager final {
 public:
  LevelManager() = default;
  ~LevelManager() = default;

 public:
  /**
   * @brief Initialize the level manager
   * @param levels_path Path to the levels directory
   * @param registry Registry instance
   * @param archetype_manager Archetype manager instance
   */
  void Initialize(
      const std::string& levels_path, const std::shared_ptr<zygarde::Registry>& registry,
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager);

  /**
   * @brief Get the levels available
   * @return A vector of levels
   */
  [[nodiscard]] inline std::vector<Level> GetLevels() const { return levels_; }

  /**
   * @brief Select a level by its name, this will be the level that will be played once StartLevel
   * is called
   * @param level_name The name of the level to select
   */
  void SelectLevel(const std::string& level_name);

  /**
   * @brief Start the selected level
   * @param difficulty Difficulty data to use
   */
  void StartLevel(DifficultyData difficulty);

  /**
   * @brief Update the level manager
   * @param delta_time Delta time
   */
  void Update(const utils::Timer::Nanoseconds& delta_time);

  /**
   * @brief Check if the current level is finished
   * @return True if the level is finished, false otherwise
   */
  [[nodiscard]] inline bool LevelIsFinished() const noexcept {
    return currentWaveIndex_ >= selectedLevel_.waves.size();
  }

 private:
  /// @brief Level spawn properties
  struct SpawnProps {
    /// @brief The time to spawn an enemy
    zygarde::utils::Timer::Nanoseconds spawnTime;
    /// @brief The current spawn time
    zygarde::utils::Timer::Nanoseconds currentSpawnTime;
    /// @brief The current enemy count
    int count = 0;
  };

  /// @brief Spawn cooldowns map
  using SpawnCooldowns = std::map<std::string, SpawnProps>;

 private:
  /**
   * @brief Build the spawn cooldowns for the selected level waves.
   * This will be used to spawn enemies at the right time
   */
  void BuildSpawnCooldowns();

  /**
   * @brief Compute the enemy spawn cooldown
   * @param wave_max_time The maximum time for the wave
   * @param enemy_count The amount of enemies to spawn
   * @return The computed spawn cooldown
   */
  static zygarde::utils::Timer::Nanoseconds ComputeEnemySpawnCooldown(float wave_max_time,
                                                                      int enemy_count);

  /**
   * @brief Update the spawn cooldowns
   * @param deltaTime Delta time
   */
  void UpdateSpawnCooldowns(const zygarde::utils::Timer::Nanoseconds& deltaTime);

  /**
   * @brief Check if an enemy can be spawned
   * @param enemy_name The name of the enemy
   * @param waveCooldowns The wave cooldowns
   * @return True if the enemy can be spawned, false otherwise
   */
  static bool CanSpawnEnemy(const std::string& enemy_name, const SpawnCooldowns& waveCooldowns);

  /**
   * @brief Move to the next wave
   */
  void NextWave();

 private:
  /// @brief Selected level
  Level selectedLevel_;
  /// @brief Levels available
  std::vector<Level> levels_;
  /// @brief Current wave index
  std::size_t currentWaveIndex_ = -1;
  /// @brief Current wave time
  zygarde::utils::Timer::Nanoseconds currentWaveTime_{};
  /// @brief Current wave data
  Wave currentWave_;
  /// @brief Level spawn cooldowns
  std::vector<SpawnCooldowns> levelSpawnCooldowns_;
  /// @brief Ongoing spawn cooldowns
  std::vector<SpawnCooldowns> ongoingSpawnCooldowns_;
  /// @brief Enemy spawner
  EnemySpawner enemySpawner_;
};
}  // namespace rtype::server::game
