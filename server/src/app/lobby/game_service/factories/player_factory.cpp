/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.cpp
*/

#include "player_factory.hpp"

#include <iostream>

#include "game/includes/constants.hpp"
#include "scripting/components/script/script.hpp"

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
  scripting::types::Collision2DFunction onCollisionEnter = HandleCollision;

  registry->AddComponent<scripting::components::Script>(
      entity, {onCollisionEnter, std::nullopt, valuesMap});
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
