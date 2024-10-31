/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.cpp
*/

#include "enemy_manager.hpp"

#include <random>

#include "app/room/game_service/archetype_keys.hpp"
#include "app/room/game_service/scripts/enemies/pata_script.hpp"
#include "core/components/position/position.hpp"
#include "scripting/components/pool/script_pool.hpp"

void rtype::server::game::EnemyManager::Update(
    const utils::Timer::Nanoseconds &delta_time, Registry::Const_Ptr registry,
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> &archetype_manager) {
  accumulatedTime_ += delta_time;

  if (accumulatedTime_ < std::chrono::milliseconds(3000)) {
    return;
  }
  accumulatedTime_ = std::chrono::milliseconds(0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution dist(80.0f, 1000.0f);

  const core::types::Vector3f position(2000, dist(gen), 0);
  auto entity = archetype_manager->InvokeArchetype(registry, tools::kArchetypeEnemyPataNormal);
  auto scriptPool = registry->GetComponent<zygarde::scripting::components::ScriptPool>(entity);
  auto positionComponent = registry->GetComponent<core::components::Position>(entity);
  if (scriptPool.has_value() && scriptPool.value()) {
    auto script = scriptPool.value()->GetScript<scripts::PataScript>();
    script->SetBasePosition(position);
  }
  if (positionComponent.has_value() && positionComponent.value()) {
    positionComponent.value()->point = position;
  }
}
