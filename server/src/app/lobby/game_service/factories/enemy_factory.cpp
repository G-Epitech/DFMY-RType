/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyFactory.cpp
*/

#include "enemy_factory.hpp"

#include "game/includes/constants.hpp"
#include "projectile_factory.hpp"
#include "scripting/components/script/script.hpp"
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
  CreateScript(registry, enemy);
  return enemy;
}

void EnemyFactory::CreateScript(Registry::Const_Ptr registry, const Entity& entity) {
  auto basePosition = registry->GetComponent<core::components::Position>(entity);

  scripting::types::ValuesMap valuesMap;
  valuesMap["basePosition"] = basePosition->point;
  valuesMap["health"] = 50;
  valuesMap["goingUp"] = true;
  valuesMap["upperLimit"] = basePosition->point.y + 30.0f;
  valuesMap["lowerLimit"] = basePosition->point.y - 30.0f;
  valuesMap["lastShootTime"] = utils::Timer::Nanoseconds::zero();

  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;
  scripting::types::FixedUpdateFunction fixedUpdate = FixedUpdate;

  registry->AddComponent<scripting::components::Script>(entity,
                                                        {onCollisionEnter, fixedUpdate, valuesMap});
}

void EnemyFactory::HandleCollision(scripting::types::ScriptingContext::ConstPtr context,
                                   const physics::types::Collision2D::ptr& collision) {
  auto enemyHealth = std::any_cast<int>(context->values->at("health"));
  auto rb = collision.get()->otherRigidbody;
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
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
  auto basePosition = std::any_cast<core::types::Vector3f>(context->values->at("basePosition"));
  auto goingUp = std::any_cast<bool>(context->values->at("goingUp"));
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  auto upperLimit = std::any_cast<float>(context->values->at("upperLimit"));
  auto lowerLimit = std::any_cast<float>(context->values->at("lowerLimit"));
  auto lastShootTime =
      std::any_cast<std::chrono::nanoseconds>(context->values->at("lastShootTime"));

  lastShootTime += context->deltaTime;
  if (lastShootTime >= std::chrono::seconds(1)) {
    (*context->values)["lastShootTime"] = utils::Timer::Nanoseconds::zero();
    auto bullet = ProjectileFactory::CreateProjectile(context->registry, position->point, {32, 15},
                                                      sdk::game::types::GameEntityType::kEnemy);
  } else {
    (*context->values)["lastShootTime"] = lastShootTime;
  }
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
    rb->SetVelocity({-100.0f, verticalSpeed});
  } else {
    rb->SetVelocity({-100.0f, -verticalSpeed});
  }
  (*context->values)["goingUp"] = goingUp;
}
