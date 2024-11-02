/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** mono_behaviour.hpp
*/

#pragma once

#include <iostream>

#include "api.hpp"
#include "physics/2d/types/collision_2d.hpp"
#include "registry.hpp"
#include "scripting/types/scripting_context.hpp"
#include "scripting/types/values_map.hpp"

namespace zygarde::scripting::components {

class EXPORT_ZYGARDE_API MonoBehaviour {
 public:
  using Instance = std::shared_ptr<MonoBehaviour>;

 public:
  virtual ~MonoBehaviour() = default;

  /**
   * @brief Called when the MonoBehaviour is enabled
   * @param customScriptValues Custom values passed to the script
   */
  virtual void OnEnable(const scripting::types::ValuesMap& customScriptValues) = 0;

  /**
   * @brief Function each tick by the script execution system
   * @param context Scripting context
   */
  virtual void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) = 0;

  /**
   * @brief Called when the entity enters a collision
   * @param context Scripting context
   * @param collision Collision object
   */
  virtual void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                                const physics::types::Collision2D::ptr& collision) = 0;
};
}  // namespace zygarde::scripting::components
