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

  void Update(const zygarde::utils::Timer::Nanoseconds &delta_time,
              zygarde::Registry::Const_Ptr registry,
              const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> &archetypeManager);

 private:
  zygarde::utils::Timer::Nanoseconds accumulatedTime_;
};
}  // namespace rtype::server::game
