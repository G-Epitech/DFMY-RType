/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Script.hpp
*/

#pragma once

#include "api.hpp"
#include "scripting/types/callbacks.hpp"

namespace zygarde::scripting::systems {
class ScriptExecutionSystem;
}

namespace zygarde::scripting::components {
class EXPORT_ZYGARDE_API Script final {
 public:
  Script() = default;
  ~Script() = default;

  Script(std::optional<types::Collision2DFunction> on_collision_enter,
         std::optional<types::FixedUpdateFunction> fixed_update, const types::ValuesMap& values);

  Script(std::optional<types::Collision2DFunction> on_collision_enter,
         std::optional<types::FixedUpdateFunction> fixed_update);

 public:
  std::optional<types::Collision2DFunction> onCollisionEnter;
  std::optional<types::FixedUpdateFunction> fixedUpdate;

  friend class zygarde::scripting::systems::ScriptExecutionSystem;

 private:
  std::shared_ptr<types::ValuesMap> values_;
};
}  // namespace zygarde::scripting::components
