/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyFactory.cpp
*/

#include "enemy_factory.hpp"

#include "app/lobby/game_service/scripts/enemies/pata_script.hpp"
#include "game/includes/constants.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripting/types/callbacks.hpp"

using namespace rtype::server::game;

Entity EnemyFactory::CreateEnemy(Registry::Const_Ptr registry,
                                 const core::types::Vector3f& position,
                                 const sdk::game::types::EnemyType enemy_type) {
  Entity enemy = registry->SpawnEntity();
  core::types::Vector2f box_size;

  if (enemy_type == rtype::sdk::game::types::EnemyType::kPata) {
    box_size = {61, 108};
  }
  registry->AddComponent<physics::components::Rigidbody2D>(enemy, {});
  registry->AddComponent<core::components::Position>(enemy, {position});
  registry->AddComponent<physics::components::BoxCollider2D>(
      enemy, {box_size, sdk::game::constants::kEnemyCollisionLayers,
              sdk::game::constants::kEnemyBulletIncludeLayers});
  registry->AddComponent<core::components::Tags>(
      enemy,
      core::components::Tags({sdk::game::constants::kEnemyTag, sdk::game::constants::kPataTag}));
  std::vector<std::shared_ptr<scripting::components::MonoBehaviour>> scripts;
  scripts.push_back(std::make_shared<scripts::PataScript>(position));
  registry->AddComponent<scripting::components::ScriptPool>(
      enemy, scripting::components::ScriptPool(scripts));
  return enemy;
}
