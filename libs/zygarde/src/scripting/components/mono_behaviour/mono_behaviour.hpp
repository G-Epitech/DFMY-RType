/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** mono_behaviour.hpp
*/

#pragma once

#include "api.hpp"
#include "physics/2d/types/collision_2d.hpp"
#include "registry.hpp"
#include "scripting/types/context.hpp"

namespace zygarde::scripting::components {
class EXPORT_ZYGARDE_API MonoBehaviour {
 public:
  MonoBehaviour() = default;
  virtual ~MonoBehaviour() = default;

  virtual void OnEnable() {}

  virtual void OnDisable() {};

  virtual void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {};

  virtual void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                                const physics::types::Collision2D::ptr& collision) {};
};
}  // namespace zygarde::scripting::components
