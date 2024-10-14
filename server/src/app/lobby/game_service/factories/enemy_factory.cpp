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
      enemy, zygarde::core::components::Tags({sdk::game::constants::kEnemyTag}));
  CreateScript(registry, enemy);
  return enemy;
}

void EnemyFactory::CreateScript(zygarde::Registry::Const_Ptr registry, const Entity& entity) {
  auto basePosition = registry->GetComponent<zygarde::core::components::Position>(entity);

  zygarde::scripting::types::ValuesMap valuesMap;
  valuesMap["basePosition"] = basePosition->point;
  valuesMap["health"] = 50;
  valuesMap["goingUp"] = true;
  valuesMap["upperLimit"] = basePosition->point.y + 30.0f;
  valuesMap["lowerLimit"] = basePosition->point.y - 30.0f;

  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;
  scripting::types::FixedUpdateFunction fixedUpdate = FixedUpdate;

  registry->AddComponent<zygarde::scripting::components::Script>(
      entity, {onCollisionEnter, fixedUpdate, valuesMap});
}

void EnemyFactory::HandleCollision(scripting::types::ScriptingContext::ConstPtr context,
                                   const physics::types::Collision2D::ptr& collision) {
  auto enemyHealth = std::any_cast<int>(context->values->at("health"));
  auto rb = collision.get()->otherRigidbody;
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<zygarde::core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }

  if (*otherEntityTag == rtype::sdk::game::constants::kPlayerBulletTag) {
    enemyHealth -= 10;
    (*context->values)["health"] = enemyHealth;
  }
  if (enemyHealth <= 0) {
    context->registry->DestroyEntity(context->me);
  }
}

void EnemyFactory::FixedUpdate(scripting::types::ScriptingContext::ConstPtr context) {
  auto basePosition =
      std::any_cast<zygarde::core::types::Vector3f>(context->values->at("basePosition"));
  auto goingUp = std::any_cast<bool>(context->values->at("goingUp"));
  auto position = context->registry->GetComponent<zygarde::core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<zygarde::physics::components::Rigidbody2D>(context->me);
  auto upperLimit = std::any_cast<float>(context->values->at("upperLimit"));
  auto lowerLimit = std::any_cast<float>(context->values->at("lowerLimit"));

  if (!position || !rb) {
    return;
  }
  if (position->point.y >= upperLimit) {
    goingUp = false;
  } else if (position->point.y <= lowerLimit) {
    goingUp = true;
  }
  float verticalSpeed = 20.0f;
  if (goingUp) {
    rb->SetVelocity({-3.0f, verticalSpeed});
  } else {
    rb->SetVelocity({-3.0f, -verticalSpeed});
  }
  (*context->values)["goingUp"] = goingUp;
}
