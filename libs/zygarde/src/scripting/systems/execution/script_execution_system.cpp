/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.cpp
*/

#include "script_execution_system.hpp"

using namespace zygarde::scripting::systems;

ScriptExecutionSystem::ScriptExecutionSystem(const utils::Timer::Nanoseconds& deltaTime)
    : deltaTime_{deltaTime} {}

void ScriptExecutionSystem::Run(Registry::Ptr r,
                                sparse_array<scripting::components::Script>::ptr scripts) {
  for (currentScriptIndex_; currentScriptIndex_ < scripts->size(); currentScriptIndex_++) {
    auto& scriptComponent = (*scripts)[currentScriptIndex_];
    if (!scriptComponent.has_value()) {
      continue;
    }
    ProcessScript(r, &scriptComponent.value());
  }
}

void ScriptExecutionSystem::ProcessScript(Registry::Const_Ptr registry,
                                          scripting::components::Script* script) {
  types::ScriptingContext context = CreateContext(registry, script);

  HandleFixedUpdate(registry, script, context);
  HandleCollisionCallback(registry, script, context);
}

scripting::types::ScriptingContext ScriptExecutionSystem::CreateContext(
    Registry::Const_Ptr registry, scripting::components::Script* script) {
  return {registry, script->values_, deltaTime_};
}

void ScriptExecutionSystem::HandleCollisionCallback(
    Registry::Const_Ptr registry, scripting::components::Script* script,
    scripting::types::ScriptingContext& context) const {
  if (!script->onCollisionEnter.has_value()) {
    return;
  }
  zygarde::Entity entity = registry->EntityFromIndex(currentScriptIndex_);
  auto collider = registry->GetComponent<physics::components::BoxCollider2D>(entity);

  if (!collider) {
    return;
  }
  while (collider->HasCollision()) {
    auto collision = collider->GetNextCollision();
    script->onCollisionEnter.value()(context, collision);
  }
}

void ScriptExecutionSystem::HandleFixedUpdate(Registry::Const_Ptr registry,
                                              scripting::components::Script* script,
                                              scripting::types::ScriptingContext& context) {
  if (script->fixedUpdate.has_value()) {
    script->fixedUpdate.value()(context);
  }
}
