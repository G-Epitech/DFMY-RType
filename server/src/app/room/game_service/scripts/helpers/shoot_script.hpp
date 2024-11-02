/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootScript.hpp
*/

#pragma once

#include "zygarde/src/core/types/vector/vector_3f.hpp"
#include "zygarde/src/scripting/types/scripting_context.hpp"

namespace rtype::server::game::scripts {
class ShootHelper {
 public:
  ShootHelper() = delete;
  ~ShootHelper() = delete;

  static void SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                          const zygarde::core::types::Vector3f& position_offset, float damage_mul,
                          const std::string& projectile_archetype);
};
}  // namespace rtype::server::game::scripts
