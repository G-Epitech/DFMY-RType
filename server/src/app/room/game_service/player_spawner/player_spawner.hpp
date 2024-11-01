/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_spawner.hpp
*/

#pragma once

#include "types/difficulty.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"

namespace rtype::server::game {
class PlayerSpawner {
 public:
  PlayerSpawner() = default;
  ~PlayerSpawner() = default;

  void Initialize(
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager,
      const std::shared_ptr<zygarde::Registry>& registry);

  inline void SetDifficulty(const Difficulty& difficulty) noexcept { difficulty_ = difficulty; }

  zygarde::Entity SpawnPlayer(std::uint64_t player_id);

 private:
  Difficulty difficulty_;
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
