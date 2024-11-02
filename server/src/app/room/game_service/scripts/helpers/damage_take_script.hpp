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

  static void HandleDamageTake(float* health,
                               const std::shared_ptr<scripting::types::ScriptingContext>& context,
                               const Entity& other_entity);
};
}  // namespace rtype::server::game::scripts
