/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.cpp
*/

#include "projectile_factory.hpp"

#include <iostream>

#include "scripting/components/script/script.hpp"

using namespace rtype::server::game;

zygarde::Entity ProjectileFactory::CreateProjectile(zygarde::Registry::Const_Ptr registry,
                                                    const core::types::Vector3f& position,
                                                    const core::types::Vector2f& box_size) {
  Entity projectile = registry->SpawnEntity();

  registry->AddComponent<zygarde::physics::components::Rigidbody2D>(
      projectile,
      zygarde::physics::components::Rigidbody2D(zygarde::core::types::Vector2f::left()));
  registry->AddComponent<zygarde::core::components::Position>(projectile, {position});
  registry->AddComponent<zygarde::physics::components::BoxCollider2D>(
      projectile, {box_size, sdk::game::constants::kPlayerCollidesWith});
  registry->AddComponent<zygarde::core::components::Tags>(
      projectile, zygarde::core::components::Tags(sdk::game::constants::kEnemyBulletTag));
  registry->AddComponent<zygarde::scripting::components::Script>(projectile, {});
  CreateScript(registry, projectile);
  return projectile;
}

void ProjectileFactory::CreateScript(zygarde::Registry::Const_Ptr registry, const Entity& entity) {
  zygarde::scripting::types::ValuesMap valuesMap;

  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<zygarde::scripting::components::Script>(
      entity, {onCollisionEnter, std::nullopt, valuesMap});
}

void ProjectileFactory::HandleCollision(const scripting::types::ScriptingContext& context,
                                        const physics::types::Collision2D::ptr& collision) {
  context.registry->KillEntity(context.me);
  std::cout << "I died" << std::endl;
}
