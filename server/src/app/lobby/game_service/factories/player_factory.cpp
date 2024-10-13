/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.cpp
*/

#include "player_factory.hpp"

#include <iostream>

#include "scripting/components/script/script.hpp"

using namespace rtype::server::game;

zygarde::Entity PlayerFactory::CreatePlayer(zygarde::Registry::Const_Ptr registry,
                                            const zygarde::core::types::Vector3f &position,
                                            const zygarde::core::types::Vector2f &box_size) {
  Entity player = registry->SpawnEntity();

  registry->AddComponent<zygarde::physics::components::Rigidbody2D>(player, {});
  registry->AddComponent<zygarde::core::components::Position>(player, {position});
  registry->AddComponent<zygarde::physics::components::BoxCollider2D>(
      player, {box_size, sdk::game::constants::kPlayerCollidesWith});
  registry->AddComponent<zygarde::core::components::Tags>(
      player, zygarde::core::components::Tags(sdk::game::constants::kPlayerTag));
  CreateScript(registry, player);
  return player;
}

void PlayerFactory::CreateScript(zygarde::Registry::Const_Ptr registry, const Entity &entity) {
  zygarde::scripting::types::ValuesMap valuesMap;

  valuesMap["health"] = 100;
  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<zygarde::scripting::components::Script>(
      entity, {onCollisionEnter, std::nullopt, valuesMap});
}

void PlayerFactory::HandleCollision(const scripting::types::ScriptingContext &context,
                                    const physics::types::Collision2D::ptr &collision) {
  auto playerHealth = std::any_cast<int>(context.values.at("health"));
  auto rb = collision.get()->otherRigidbody;
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context.registry->GetComponent<zygarde::core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }
  if (*otherEntityTag == rtype::sdk::game::constants::kEnemyBulletTag) {
    playerHealth -= 10;
    context.values["health"] = playerHealth;
  }
  if (playerHealth <= 0) {
    context.registry->DestroyEntity(context.me);
  }
}
