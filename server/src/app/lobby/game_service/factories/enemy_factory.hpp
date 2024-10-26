/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyFactory.hpp
*/

#pragma once

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

  static Entity CreateEnemy(Registry::Const_Ptr registry, const core::types::Vector3f &position,
                            sdk::game::types::EnemyType enemy_type);
};
}  // namespace rtype::server::game
