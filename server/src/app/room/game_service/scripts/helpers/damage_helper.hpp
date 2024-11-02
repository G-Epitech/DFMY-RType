/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** damage_take_script.hpp
*/

#pragma once

#include "zygarde/src/scripting/types/scripting_context.hpp"

namespace rtype::server::game::scripts {
class DamageHelper {
 public:
  DamageHelper() = delete;
  ~DamageHelper() = delete;

  /**
   * @brief Handle the damage taken by an entity
   * @param health Health of the entity
   * @param context Context of the entity
   * @param other_entity Entity that caused the damage
   */
  static void HandleDamageTake(float* health,
                               const std::shared_ptr<scripting::types::ScriptingContext>& context,
                               const Entity& other_entity);
};
}  // namespace rtype::server::game::scripts
