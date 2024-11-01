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
  /**
   * @brief Construct a new Script Execution System object
   * @param deltaTime Delta time
   * @param archetypeManager Archetype manager instance (for the scripting context)
   */
  explicit ScriptExecutionSystem(
      const utils::Timer::Nanoseconds &deltaTime,
      const std::shared_ptr<core::archetypes::ArchetypeManager> &archetypeManager);

  ~ScriptExecutionSystem() override = default;

 public:
  /**
   * @brief Run the script execution system
   * @param r Registry
   * @param scripts Pools of scripts to run
   */
  void Run(Registry::Ptr r, zipper<scripting::components::ScriptPool> scripts) override;

 private:
  /**
   * @brief Process a script pool
   * @param registry Registry
   * @param script Script pool to process
   */
  void ProcessScriptPool(Registry::Const_Ptr registry, scripting::components::ScriptPool *script);

  /**
   * @brief Process a script collision callbacks
   * @param registry Registry
   * @param script Script to process
   * @param context Scripting context
   */
  void HandleCollisionCallback(Registry::Const_Ptr registry,
                               const std::shared_ptr<scripting::components::MonoBehaviour> &script,
                               types::ScriptingContext::ConstPtr context) const;

  /**
   * @brief Create a scripting context
   * @param registry Registry
   * @return Scripting context
   */
  types::ScriptingContext CreateContext(Registry::Const_Ptr registry);

 private:
  /// @brief Delta time
  const utils::Timer::Nanoseconds &deltaTime_;
  /// @brief Current script index mainly used for utility
  std::size_t currentScriptIndex_ = 0;
  /// @brief Archetype manager instance
  std::shared_ptr<core::archetypes::ArchetypeManager> archetypeManager_;
};
}  // namespace zygarde::scripting::systems
