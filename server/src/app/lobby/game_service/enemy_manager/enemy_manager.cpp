/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.cpp
*/

#include "enemy_manager.hpp"

#include <random>

#include "app/lobby/game_service/archetype_keys.hpp"
#include "core/components/position/position.hpp"

void rtype::server::game::EnemyManager::Update(
    const utils::Timer::Nanoseconds &delta_time, Registry::Const_Ptr registry,
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> &archetype_manager) {
  accumulatedTime_ += delta_time;

  if (accumulatedTime_ < std::chrono::milliseconds(1500)) {
    return;
  }
  accumulatedTime_ = std::chrono::milliseconds(0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution dist(80.0f, 1000.0f);

  const core::types::Vector3f position(2000, dist(gen), 0);
  auto entity = archetype_manager->InvokeArchetype(registry, tools::kArchetypeEnemyPataNormal);
  auto positionComponent = registry->GetComponent<core::components::Position>(entity);
  positionComponent->point = position;
}
