/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.cpp
*/

#include "player_factory.hpp"

#include <iostream>

#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "projectile_factory.hpp"
#include "scripting/components/script/script.hpp"
#include "types/weapons.hpp"

using namespace rtype::server::game;

Entity PlayerFactory::CreatePlayer(Registry::Const_Ptr registry,
                                   const core::types::Vector3f &position,
                                   const core::types::Vector2f &box_size) {
  Entity player = registry->SpawnEntity();

  registry->AddComponent<physics::components::Rigidbody2D>(player, {});
  registry->AddComponent<core::components::Position>(player, {position});
  registry->AddComponent<physics::components::BoxCollider2D>(
      player, {box_size, sdk::game::constants::kPlayerCollisionLayers,
               sdk::game::constants::kPlayerIncludeLayers});
  registry->AddComponent<core::components::Tags>(
      player, core::components::Tags({sdk::game::constants::kPlayerTag}));
  CreateScript(registry, player);
  return player;
}

void PlayerFactory::CreateScript(Registry::Const_Ptr registry, const Entity &entity) {
  scripting::types::ValuesMap valuesMap;

  valuesMap["health"] = 100;
  valuesMap["equippedWeapon"] = sdk::game::types::WeaponType::kBasic;
  valuesMap["shootCooldown"] =
      sdk::game::utils::GetFireRate(sdk::game::stats::WeaponBasic::fireRate);
  valuesMap["lastShootTime"] = std::chrono::nanoseconds::zero();
  valuesMap["shoot"] = false;

  scripting::types::FixedUpdateFunction fixedUpdate = FixedUpdate;
  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<scripting::components::Script>(entity,
                                                        {onCollisionEnter, fixedUpdate, valuesMap});
}

void PlayerFactory::HandleCollision(scripting::types::ScriptingContext::ConstPtr context,
                                    const physics::types::Collision2D::ptr &collision) {
  auto playerHealth = std::any_cast<int>(context->values->at("health"));
  auto rb = collision.get()->otherRigidbody;
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }
  if (*otherEntityTag == rtype::sdk::game::constants::kEnemyBulletTag) {
    std::cout << "Player hit by enemy bullet" << std::endl;
    playerHealth -= 10;
    (*context->values)["health"] = playerHealth;
  }
  if (playerHealth <= 0) {
    context->registry->DestroyEntity(context->me);
  }
}

void PlayerFactory::FixedUpdate(scripting::types::ScriptingContext::ConstPtr context) {
  auto shoot = std::any_cast<bool>(context->values->at("shoot"));
  auto lastShootTime =
      std::any_cast<std::chrono::nanoseconds>(context->values->at("lastShootTime"));
  auto shootCooldown =
      std::any_cast<std::chrono::nanoseconds>(context->values->at("shootCooldown"));

  auto position = context->registry->GetComponent<core::components::Position>(context->me);

  lastShootTime += context->deltaTime;

  if (shoot && lastShootTime >= shootCooldown) {
    (*context->values)["lastShootTime"] = utils::Timer::Nanoseconds::zero();
    (*context->values)["shoot"] = false;
    ProjectileFactory::CreateProjectile(context->registry, position->point, {5, 5},
                                        sdk::game::types::GameEntityType::kPlayer);
    return;
  }
  (*context->values)["shoot"] = false;
  (*context->values)["lastShootTime"] = lastShootTime;
}
