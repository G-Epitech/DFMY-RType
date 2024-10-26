/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.cpp
*/

#include "script_execution_system.hpp"

#include <iostream>

using namespace zygarde::scripting::systems;

ScriptExecutionSystem::ScriptExecutionSystem(const utils::Timer::Nanoseconds& deltaTime)
    : deltaTime_{deltaTime} {}

void ScriptExecutionSystem::Run(Registry::Ptr r,
                                sparse_array<scripting::components::MonoBehaviour>::ptr scripts) {
  for (currentScriptIndex_; currentScriptIndex_ < scripts->size(); currentScriptIndex_++) {
    auto& scriptComponent = (*scripts)[currentScriptIndex_];
    if (scriptComponent.has_value() && r->HasEntityAtIndex(currentScriptIndex_)) {
      ProcessScript(r, &scriptComponent.value());
    }
  }
  currentScriptIndex_ = 0;
}

void ScriptExecutionSystem::ProcessScript(Registry::Const_Ptr registry,
                                          scripting::components::MonoBehaviour* script) {
  std::shared_ptr<types::ScriptingContext> context =
      std::make_shared<types::ScriptingContext>(CreateContext(registry, script));

  script->FixedUpdate(context);
  HandleCollisionCallback(registry, script, context);
}

scripting::types::ScriptingContext ScriptExecutionSystem::CreateContext(
    Registry::Const_Ptr registry, scripting::components::MonoBehaviour* script) {
  return {registry, deltaTime_, registry->EntityFromIndex(currentScriptIndex_)};
}

void ScriptExecutionSystem::HandleCollisionCallback(
    Registry::Const_Ptr registry, scripting::components::MonoBehaviour* script,
    types::ScriptingContext::ConstPtr context) const {
  zygarde::Entity entity = registry->EntityFromIndex(currentScriptIndex_);
  auto collider = registry->GetComponent<physics::components::BoxCollider2D>(entity);
  if (!collider) {
    return;
  }
  while (collider->HasCollision()) {
    auto collision = collider->GetNextCollision();
    script->OnCollisionEnter(context, collision);
  }
}
