/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerFactory.hpp
*/

#pragma once

#include "game/includes/constants.hpp"
#include "zygarde/src/core/components/components.hpp"
#include "zygarde/src/entity.hpp"
#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/scripting/types/callbacks.hpp"
#include "zygarde/src/scripting/types/context.hpp"

namespace rtype::server::game {
class PlayerFactory {
 public:
  PlayerFactory() = delete;
  ~PlayerFactory() = delete;

  static zygarde::Entity CreatePlayer(zygarde::Registry::Const_Ptr registry,
                                      const zygarde::core::types::Vector3f &position,
                                      const zygarde::core::types::Vector2f &box_size);

 private:
  static void CreateScript(zygarde::Registry::Const_Ptr registry, const zygarde::Entity &entity);

  static void HandleCollision(const zygarde::scripting::types::ScriptingContext &context,
                              const physics::types::Collision2D::ptr &collision);
};
}  // namespace rtype::server::game
