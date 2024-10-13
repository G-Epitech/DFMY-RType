/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.cpp
*/

#include "player_factory.hpp"

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
  registry->AddComponent<zygarde::scripting::components::Script>(player, {});
  return player;
}
