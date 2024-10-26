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
                                sparse_array<scripting::components::ScriptPool>::ptr script_pools) {
  for (currentScriptIndex_; currentScriptIndex_ < script_pools->size(); currentScriptIndex_++) {
    auto& scriptComponent = (*script_pools)[currentScriptIndex_];
    if (scriptComponent.has_value() && r->HasEntityAtIndex(currentScriptIndex_)) {
      ProcessScriptPool(r, &scriptComponent.value());
    }
  }
  currentScriptIndex_ = 0;
}

void ScriptExecutionSystem::ProcessScriptPool(Registry::Const_Ptr registry,
                                              scripting::components::ScriptPool* script_pool) {
  std::shared_ptr<types::ScriptingContext> context =
      std::make_shared<types::ScriptingContext>(CreateContext(registry));
  auto scripts = script_pool->GetScripts();

  for (auto& script : scripts) {
    script->FixedUpdate(context);
    HandleCollisionCallback(registry, script, context);
  }
}

scripting::types::ScriptingContext ScriptExecutionSystem::CreateContext(
    Registry::Const_Ptr registry) {
  return {registry, deltaTime_, registry->EntityFromIndex(currentScriptIndex_)};
}

void ScriptExecutionSystem::HandleCollisionCallback(
    Registry::Const_Ptr registry,
    const std::shared_ptr<scripting::components::MonoBehaviour>& script,
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
