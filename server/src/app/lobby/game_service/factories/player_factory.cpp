/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.cpp
*/

#include "player_factory.hpp"

#include <iostream>

#include "libs/zygarde/src/scripting/components/pool/script_pool.hpp"
#include "projectile_factory.hpp"

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
  std::vector<std::shared_ptr<scripting::components::MonoBehaviour>> scripts;
  scripts.push_back(std::make_shared<scripts::PlayerScript>());
  registry->AddComponent<scripting::components::ScriptPool>(
      player, scripting::components::ScriptPool(scripts));
  return player;
}
