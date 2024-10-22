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
      projectile, physics::components::Rigidbody2D(direction * 200));
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
  scripting::types::FixedUpdateFunction onFixedUpdate =
      [](scripting::types::ScriptingContext::ConstPtr context) {
        const auto posComponent =
            context->registry->GetComponent<core::components::Position>(context->me);
        if (posComponent->point.x > 2000 || posComponent->point.x < -200) {
          context->registry->DestroyEntity(context->me);
          std::cout << "I died because I'm out of bounds\n";
        }
      };

  registry->AddComponent<scripting::components::Script>(
      entity, {onCollisionEnter, onFixedUpdate, valuesMap});
}

void ProjectileFactory::HandleCollision(scripting::types::ScriptingContext::ConstPtr context,
                                        const physics::types::Collision2D::ptr& collision) {
  context->registry->DestroyEntity(context->me);
  std::cout << "I died\n";
}
