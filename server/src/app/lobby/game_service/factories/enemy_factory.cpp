/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyFactory.cpp
*/

#include "enemy_factory.hpp"

#include <iostream>

#include "scripting/components/script/script.hpp"
#include "scripting/types/callbacks.hpp"

using namespace rtype::server::game;

zygarde::Entity EnemyFactory::CreateEnemy(zygarde::Registry::Const_Ptr registry,
                                          const core::types::Vector3f& position,
                                          rtype::sdk::game::types::EnemyType enemy_type) {
  Entity enemy = registry->SpawnEntity();
  zygarde::core::types::Vector2f box_size;

  if (enemy_type == rtype::sdk::game::types::EnemyType::kPata) {
    box_size = {20, 20};
  }
  registry->AddComponent<zygarde::physics::components::Rigidbody2D>(enemy, {});
  registry->AddComponent<zygarde::core::components::Position>(enemy, {position});
  registry->AddComponent<zygarde::physics::components::BoxCollider2D>(
      enemy, {box_size, sdk::game::constants::kEnemyCollidesWith});
  registry->AddComponent<zygarde::core::components::Tags>(
      enemy, zygarde::core::components::Tags(sdk::game::constants::kEnemyTag));
  CreateScript(registry, enemy);
  return enemy;
}

void EnemyFactory::CreateScript(zygarde::Registry::Const_Ptr registry, const Entity& entity) {
  zygarde::scripting::types::ValuesMap valuesMap;

  valuesMap["health"] = 50;
  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<zygarde::scripting::components::Script>(
      entity, {onCollisionEnter, std::nullopt, valuesMap});
}

void EnemyFactory::HandleCollision(const scripting::types::ScriptingContext& context,
                                   const physics::types::Collision2D::ptr& collision) {
  auto enemyHealth = std::any_cast<int>(context.values.at("health"));
  auto rb = collision.get()->otherRigidbody;
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context.registry->GetComponent<zygarde::core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }

  if (*otherEntityTag == rtype::sdk::game::constants::kPlayerBulletTag) {
    enemyHealth -= 10;
    context.values["health"] = enemyHealth;
  }
  if (enemyHealth <= 0) {
    context.registry->DestroyEntity(context.me);
  }
}
