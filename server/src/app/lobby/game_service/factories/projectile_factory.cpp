/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.cpp
*/

#include "projectile_factory.hpp"

#include <iostream>

#include "game/includes/constants.hpp"
#include "scripting/components/script/script.hpp"

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

  if (shooter == sdk::game::types::GameEntityType::kPlayer) {
    direction = core::types::Vector2f::right();
    tag = sdk::game::constants::kPlayerBulletTag;
    collisionLayers = sdk::game::constants::kPlayerBulletCollisionLayers;
    includeLayers = sdk::game::constants::kPlayerBulletIncludeLayers;
  } else {
    direction = core::types::Vector2f::left();
    tag = sdk::game::constants::kEnemyBulletTag;
    collisionLayers = sdk::game::constants::kEnemyBulletCollisionLayers;
    includeLayers = sdk::game::constants::kEnemyBulletIncludeLayers;
  }

  registry->AddComponent<physics::components::Rigidbody2D>(
      projectile, physics::components::Rigidbody2D(direction * 70));
  registry->AddComponent<core::components::Position>(projectile, {position});
  registry->AddComponent<physics::components::BoxCollider2D>(
      projectile, {box_size, collisionLayers, includeLayers});
  registry->AddComponent<core::components::Tags>(projectile, core::components::Tags({tag}));
  CreateScript(registry, projectile);
  return projectile;
}

void ProjectileFactory::CreateScript(Registry::Const_Ptr registry, const Entity& entity) {
  scripting::types::ValuesMap valuesMap;

  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<scripting::components::Script>(
      entity, {onCollisionEnter, std::nullopt, valuesMap});
}

void ProjectileFactory::HandleCollision(scripting::types::ScriptingContext::ConstPtr context,
                                        const physics::types::Collision2D::ptr& collision) {
  const auto entity = collision->otherEntity;
  const auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }
  if (*otherEntityTag == sdk::game::constants::kPlayerBulletTag) {
    return;
  }
  if (*otherEntityTag == sdk::game::constants::kEnemyBulletTag) {
    return;
  }
  context->registry->DestroyEntity(context->me);
  std::cout << "I died\n";
}
