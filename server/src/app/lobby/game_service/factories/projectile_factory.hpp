/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.hpp
*/

#pragma once

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

  static Entity CreateProjectile(Registry::Const_Ptr registry,
                                 const core::types::Vector3f &position,
                                 const core::types::Vector2f &box_size,
                                 const sdk::game::types::GameEntityType shooter);
};
}  // namespace rtype::server::game
