/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.hpp
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
class ProjectileFactory {
 public:
  ProjectileFactory() = delete;
  ~ProjectileFactory() = delete;

  static zygarde::Entity CreateProjectile(zygarde::Registry::Const_Ptr registry,
                                          const zygarde::core::types::Vector3f &position,
                                          const zygarde::core::types::Vector2f &box_size,
                                          rtype::sdk::game::types::GameEntityType shooter);

 private:
  static void CreateScript(zygarde::Registry::Const_Ptr registry, const zygarde::Entity &entity);

  static void HandleCollision(const zygarde::scripting::types::ScriptingContext &context,
                              const physics::types::Collision2D::ptr &collision);
};
}  // namespace rtype::server::game
