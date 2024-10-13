/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ProjectileFactory.hpp
*/

#pragma once

#include "game/includes/constants.hpp"
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
                                      const zygarde::core::types::Vector2f &box_size);
};
}  // namespace rtype::server::game
