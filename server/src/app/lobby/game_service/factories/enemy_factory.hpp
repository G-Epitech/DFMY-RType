/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyFactory.hpp
*/

#pragma once

#include "game/includes/constants.hpp"
#include "game/includes/types.hpp"
#include "scripting/types/context.hpp"
#include "zygarde/src/core/components/components.hpp"
#include "zygarde/src/entity.hpp"
#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/registry.hpp"

namespace rtype::server::game {
class EnemyFactory {
 public:
  EnemyFactory() = delete;
  ~EnemyFactory() = delete;

  static zygarde::Entity CreateEnemy(zygarde::Registry::Const_Ptr registry,
                                     const zygarde::core::types::Vector3f &position,
                                     rtype::sdk::game::types::EnemyType enemy_type);

 private:
  static void CreateScript(zygarde::Registry::Const_Ptr registry, const zygarde::Entity &entity);

  static void FixedUpdate(zygarde::scripting::types::ScriptingContext::ConstPtr context);

  static void HandleCollision(zygarde::scripting::types::ScriptingContext::ConstPtr context,
                              const physics::types::Collision2D::ptr &collision);
};
}  // namespace rtype::server::game
