/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_spawner.cpp
*/

#include "enemy_spawner.hpp"

#include <random>

#include "app/room/game_service/archetype_keys.hpp"
#include "app/room/game_service/scripts/enemies/pata_script.hpp"
#include "core/components/position/position.hpp"
#include "scripting/components/pool/script_pool.hpp"

using namespace rtype::server::game;

void EnemySpawner::Initialize(
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetypeManager,
    const std::shared_ptr<zygarde::Registry>& registry) {
  archetypeManager_ = archetypeManager;
  registry_ = registry;
}

void EnemySpawner::SpawnEnemy(const std::string& enemy_archetype_name) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution dist(80.0f, 1000.0f);

  const core::types::Vector3f position(2000, dist(gen), 0);
  auto entity = archetypeManager_->InvokeArchetype(registry_, tools::kArchetypeEnemyPataNormal);
  auto scriptPool = registry_->GetComponent<zygarde::scripting::components::ScriptPool>(entity);
  auto positionComponent = registry_->GetComponent<core::components::Position>(entity);
  if (scriptPool.has_value() && scriptPool.value()) {
    auto script = scriptPool.value()->GetScript<scripts::PataScript>();
    script->SetBasePosition(position);
    script->SetDifficultyData(difficulty_.multipliers.enemy);
  }
  if (positionComponent.has_value() && positionComponent.value()) {
    positionComponent.value()->point = position;
  }
}
