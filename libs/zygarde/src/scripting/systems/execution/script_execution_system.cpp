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

void ScriptExecutionSystem::Run(
    Registry::Ptr r, zipper<sparse_array<scripting::components::Script>::ptr> components) {
  const auto start = components.begin();
  const auto end = components.end();
  for (auto it = start; it != end; ++it) {
    auto&& [index, values] = ~it;
    auto&& [scripts] = values;
    currentScriptIndex_ = index;
    ProcessScript(r, &scripts);
  }
  currentScriptIndex_ = 0;
}

void ScriptExecutionSystem::ProcessScript(Registry::Const_Ptr registry,
                                          scripting::components::Script* script) {
  std::shared_ptr<types::ScriptingContext> context =
      std::make_shared<types::ScriptingContext>(CreateContext(registry, script));

  HandleFixedUpdate(registry, script, context);
  HandleCollisionCallback(registry, script, context);
}

scripting::types::ScriptingContext ScriptExecutionSystem::CreateContext(
    Registry::Const_Ptr registry, scripting::components::Script* script) {
  return {registry, script->values_, deltaTime_, registry->EntityFromIndex(currentScriptIndex_)};
}

void ScriptExecutionSystem::HandleCollisionCallback(
    Registry::Const_Ptr registry, scripting::components::Script* script,
    types::ScriptingContext::ConstPtr context) const {
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

void ScriptExecutionSystem::HandleFixedUpdate(
    Registry::Const_Ptr registry, scripting::components::Script* script,
    scripting::types::ScriptingContext::ConstPtr context) {
  if (script->fixedUpdate.has_value()) {
    script->fixedUpdate.value()(context);
  }
}
