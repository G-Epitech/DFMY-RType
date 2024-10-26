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
  registry->AddComponent<scripting::components::MonoBehaviour>(player, scripts::PlayerScript());
  return player;
}
