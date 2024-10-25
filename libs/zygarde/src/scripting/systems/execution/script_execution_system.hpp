/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.hpp
*/

#pragma once

#include "api.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "scripting/components/script/script.hpp"
#include "scripting/types/context.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::scripting::systems {
class EXPORT_ZYGARDE_API ScriptExecutionSystem final
    : public ASystem<scripting::components::Script> {
 public:
  explicit ScriptExecutionSystem(const utils::Timer::Nanoseconds &deltaTime);
  ~ScriptExecutionSystem() override = default;

 public:
  void Run(Registry::Ptr r, zipper<scripting::components::Script> components) override;

 private:
  void ProcessScript(Registry::Const_Ptr registry, scripting::components::Script *script);

  static void HandleFixedUpdate(Registry::Const_Ptr registry, scripting::components::Script *script,
                                types::ScriptingContext::ConstPtr context);

  void HandleCollisionCallback(Registry::Const_Ptr registry, scripting::components::Script *script,
                               types::ScriptingContext::ConstPtr context) const;

  types::ScriptingContext CreateContext(Registry::Const_Ptr registry,
                                        scripting::components::Script *script);

 private:
  const utils::Timer::Nanoseconds &deltaTime_;
  std::size_t currentScriptIndex_ = 0;
};
}  // namespace zygarde::scripting::systems
