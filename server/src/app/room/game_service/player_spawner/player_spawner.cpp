/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_spawner.cpp
*/

#include "player_spawner.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "core/components/position/position.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"

using namespace rtype::server::game;

void PlayerSpawner::Initialize(
    const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager>& archetype_manager,
    const std::shared_ptr<zygarde::Registry>& registry) {
  archetypeManager_ = archetype_manager;
  registry_ = registry;
}

zygarde::Entity PlayerSpawner::SpawnPlayer(std::uint64_t player_id) {
  Entity player = archetypeManager_->InvokeArchetype(registry_, tools::kArchetypePlayerPhoton);

  auto position = registry_->GetComponent<core::components::Position>(player);
  if (!position.has_value() || !position.value()) {
    return player;
  }
  (*position)->point = VECTOR3F_PLAYER_OFFSET(player_id);

  auto scriptPool = registry_->GetComponent<zygarde::scripting::components::ScriptPool>(player);
  if (!scriptPool.has_value() || !scriptPool.value()) {
    return player;
  }
  auto playerScript = scriptPool.value()->GetScript<scripts::PlayerScript>();
  if (!playerScript) {
    return player;
  }
  playerScript->SetDifficultyData(difficulty_.multipliers.player);
  return player;
}
