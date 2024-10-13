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

zygarde::Entity ProjectileFactory::CreateProjectile(
    zygarde::Registry::Const_Ptr registry, const core::types::Vector3f& position,
    const core::types::Vector2f& box_size, rtype::sdk::game::types::GameEntityType shooter) {
  Entity projectile = registry->SpawnEntity();
  zygarde::core::types::Vector2f direction;
  std::string tag;
  std::vector<int> collidesWith;

  if (shooter == sdk::game::types::GameEntityType::kPlayer) {
    direction = zygarde::core::types::Vector2f::right();
    tag = sdk::game::constants::kPlayerBulletTag;
    collidesWith = sdk::game::constants::kEnemyCollidesWith;
  } else {
    direction = zygarde::core::types::Vector2f::left();
    tag = sdk::game::constants::kEnemyBulletTag;
    collidesWith = sdk::game::constants::kPlayerCollidesWith;
  }

  registry->AddComponent<zygarde::physics::components::Rigidbody2D>(
      projectile, zygarde::physics::components::Rigidbody2D(direction));
  registry->AddComponent<zygarde::core::components::Position>(projectile, {position});
  registry->AddComponent<zygarde::physics::components::BoxCollider2D>(projectile,
                                                                      {box_size, collidesWith});
  registry->AddComponent<zygarde::core::components::Tags>(projectile,
                                                          zygarde::core::components::Tags(tag));
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
  context.registry->DestroyEntity(context.me);
  std::cout << "I died" << std::endl;
}
