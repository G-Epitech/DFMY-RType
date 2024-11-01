/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.hpp
*/

#pragma once

#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class EnemyManager {
 public:
  EnemyManager() = default;
  ~EnemyManager() = default;

  /**
   * @brief Update the enemy manager, used for spawning enemies
   * @param delta_time Delta time
   * @param registry Registry
   * @param archetype_manager Archetype manager instance
   */
  void Update(
      const zygarde::utils::Timer::Nanoseconds &delta_time, zygarde::Registry::Const_Ptr registry,
      const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> &archetype_manager);

 private:
  /// @brief Accumulated time (mainly used for spawning enemies)
  zygarde::utils::Timer::Nanoseconds accumulatedTime_;
};
}  // namespace rtype::server::game
