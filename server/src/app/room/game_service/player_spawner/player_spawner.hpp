/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_spawner.hpp
*/

#pragma once

#include "types/difficulty_data.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"

#define VECTOR3F_PLAYER_OFFSET(player_id) \
  (core::types::Vector3f(487.0f, 100.0f + (100.0f * (player_id)), 0.0f))

namespace rtype::server::game {
class PlayerSpawner {
 public:
  PlayerSpawner() = default;
  ~PlayerSpawner() = default;

  /**
   * @brief Initialize the player spawner
   * @param archetype_manager Archetype manager
   * @param registry Registry
   */
  void Initialize(
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager,
      const std::shared_ptr<zygarde::Registry>& registry);

  /**
   * @brief Set the difficulty data that the player spawner should use
   * @param difficulty The difficulty data to use
   */
  inline void SetDifficulty(const DifficultyData& difficulty) noexcept { difficulty_ = difficulty; }

  /**
   * @brief Spawn a player
   * @param player_id The player ID
   * @return The player entity
   */
  zygarde::Entity SpawnPlayer(std::uint64_t player_id);

 private:
  /// @brief The difficulty data
  DifficultyData difficulty_;
  /// @brief The archetype manager
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;
  /// @brief The registry
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
