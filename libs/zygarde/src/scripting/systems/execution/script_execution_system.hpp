/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.hpp
*/

#pragma once

#include "api.hpp"
#include "core/archetypes/archetype_manager.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripting/components/script/script.hpp"
#include "scripting/types/context.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::scripting::systems {
class EXPORT_ZYGARDE_API ScriptExecutionSystem final
    : public ASystem<scripting::components::ScriptPool> {
 public:
  explicit ScriptExecutionSystem(
      const utils::Timer::Nanoseconds &deltaTime,
      const std::shared_ptr<core::archetypes::ArchetypeManager> &archetypeManager);
  ~ScriptExecutionSystem() override = default;

 public:
  void Run(Registry::Ptr r, sparse_array<scripting::components::ScriptPool>::ptr scripts) override;

 private:
  void ProcessScriptPool(Registry::Const_Ptr registry, scripting::components::ScriptPool *script);

  void HandleCollisionCallback(Registry::Const_Ptr registry,
                               const std::shared_ptr<scripting::components::MonoBehaviour> &script,
                               types::ScriptingContext::ConstPtr context) const;

  types::ScriptingContext CreateContext(Registry::Const_Ptr registry);

 private:
  const utils::Timer::Nanoseconds &deltaTime_;
  std::size_t currentScriptIndex_ = 0;
  const std::shared_ptr<core::archetypes::ArchetypeManager> &archetypeManager_;
};
}  // namespace zygarde::scripting::systems
