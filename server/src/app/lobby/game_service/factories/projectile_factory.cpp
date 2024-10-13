/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.cpp
*/

#include "projectile_factory.hpp"

#include "scripting/components/script/script.hpp"

using namespace rtype::server::game;

zygarde::Entity ProjectileFactory::CreateProjectile(zygarde::Registry::Const_Ptr registry,
                                                    const core::types::Vector3f& position,
                                                    const core::types::Vector2f& box_size) {
  Entity player = registry->SpawnEntity();

  registry->AddComponent<zygarde::physics::components::Rigidbody2D>(
      player, zygarde::physics::components::Rigidbody2D(zygarde::core::types::Vector2f::left()));
  registry->AddComponent<zygarde::core::components::Position>(player, {position});
  registry->AddComponent<zygarde::physics::components::BoxCollider2D>(
      player, {box_size, sdk::game::constants::kPlayerCollidesWith});
  registry->AddComponent<zygarde::core::components::Tags>(
      player, zygarde::core::components::Tags(sdk::game::constants::kEnemyBulletTag));
  registry->AddComponent<zygarde::scripting::components::Script>(player, {});
  return player;
}
