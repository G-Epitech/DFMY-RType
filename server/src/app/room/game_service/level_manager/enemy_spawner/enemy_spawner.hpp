/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_spawner.hpp
*/

#pragma once

#include "types/difficulty_data.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"

namespace rtype::server::game {
constexpr float kInitialEnemySpawnPositionX = 2000.0f;
constexpr float kInitialEnemySpawnPositionZ = 0.0f;
constexpr float kEnemySpawnMinPositionY = 100.0f;
constexpr float kEnemySpawnMaxPositionY = 800.0f;
}  // namespace rtype::server::game

namespace rtype::server::game {
class EnemySpawner final {
 public:
  EnemySpawner() = default;
  ~EnemySpawner() = default;

  /**
   * @brief Initialize the enemy spawner
   * @param archetypeManager Archetype manager
   * @param registry Registry
   */
  void Initialize(
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager,
      const std::shared_ptr<zygarde::Registry>& registry);

  /**
   * @param enemy_archetype_name The name of the enemy archetype
   */
  Entity SpawnEnemy(const std::string& enemy_archetype_name);

  /**
   * @brief Set the difficulty data that the enemy spawner should use
   * @param difficulty The difficulty data to use
   */
  inline void SetDifficulty(const DifficultyData& difficulty) noexcept { difficulty_ = difficulty; }

 private:
  /// @brief The difficulty data
  DifficultyData difficulty_;
  /// @brief The archetype manager
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;
  /// @brief The registry
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
