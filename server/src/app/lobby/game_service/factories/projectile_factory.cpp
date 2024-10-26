/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.cpp
*/

#include "projectile_factory.hpp"

#include <iostream>

#include "app/lobby/game_service/scripts/projectiles/base_projectile_script.hpp"
#include "libs/zygarde/src/scripting/components/pool/script_pool.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"

using namespace rtype::server::game;

Entity ProjectileFactory::CreateProjectile(Registry::Const_Ptr registry,
                                           const core::types::Vector3f& position,
                                           const core::types::Vector2f& box_size,
                                           const sdk::game::types::GameEntityType shooter) {
  Entity projectile = registry->SpawnEntity();
  core::types::Vector2f direction;
  std::string tag;
  std::vector<int> collisionLayers;
  std::vector<int> includeLayers;
  float speedMagnifier;

  if (shooter == sdk::game::types::GameEntityType::kPlayer) {
    direction = core::types::Vector2f::right();
    tag = sdk::game::constants::kPlayerBulletTag;
    collisionLayers = sdk::game::constants::kPlayerBulletCollisionLayers;
    includeLayers = sdk::game::constants::kPlayerBulletIncludeLayers;
    speedMagnifier = 700;
  } else {
    direction = core::types::Vector2f::left();
    tag = sdk::game::constants::kEnemyBulletTag;
    collisionLayers = sdk::game::constants::kEnemyBulletCollisionLayers;
    includeLayers = sdk::game::constants::kEnemyBulletIncludeLayers;
    speedMagnifier = 300;
  }

  registry->AddComponent<physics::components::Rigidbody2D>(
      projectile, physics::components::Rigidbody2D(direction * speedMagnifier));
  registry->AddComponent<core::components::Position>(projectile, {position});
  registry->AddComponent<physics::components::BoxCollider2D>(
      projectile, {box_size, collisionLayers, includeLayers});
  registry->AddComponent<core::components::Tags>(
      projectile, core::components::Tags({tag, sdk::game::constants::kBulletTag}));

  std::vector<std::shared_ptr<scripting::components::MonoBehaviour>> scripts;
  scripts.push_back(std::make_shared<scripts::BaseProjectileScript>());
  registry->AddComponent<scripting::components::ScriptPool>(
      projectile, scripting::components::ScriptPool(scripts));
  return projectile;
}
