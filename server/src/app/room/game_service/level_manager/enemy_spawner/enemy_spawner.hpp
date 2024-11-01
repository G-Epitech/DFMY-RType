/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_spawner.hpp
*/

#pragma once

#include "types/difficulty.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"

namespace rtype::server::game {
class EnemySpawner {
 public:
  EnemySpawner() = default;
  ~EnemySpawner() = default;

  void Initialize(
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager,
      const std::shared_ptr<zygarde::Registry>& registry);

  void SpawnEnemy(const std::string& enemy_name);

  inline void SetDifficulty(const Difficulty& difficulty) noexcept { difficulty_ = difficulty; }

 private:
  Difficulty difficulty_;
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
