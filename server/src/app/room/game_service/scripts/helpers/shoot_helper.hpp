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

  /**
   * @brief Spawn a bullet
   * @param context Context of the entity
   * @param position_offset Offset of the position
   * @param damage_multiplier Damage multiplier to apply
   * @param projectile_archetype Archetype of the projectile
   */
  static void SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                          const zygarde::core::types::Vector3f& position_offset,
                          float damage_multiplier, const std::string& projectile_archetype);

 private:
  static core::types::Vector3f GetProjectilePosition(
      const std::shared_ptr<scripting::types::ScriptingContext>& context,
      const zygarde::core::types::Vector3f& position_offset);
};
}  // namespace rtype::server::game::scripts
