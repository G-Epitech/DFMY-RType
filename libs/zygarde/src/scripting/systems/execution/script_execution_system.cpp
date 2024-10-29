/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.cpp
*/

#include "script_execution_system.hpp"

using namespace zygarde::scripting::systems;

ScriptExecutionSystem::ScriptExecutionSystem(
    const utils::Timer::Nanoseconds& deltaTime,
    const std::shared_ptr<core::archetypes::ArchetypeManager>& archetypeManager)
    : deltaTime_{deltaTime}, archetypeManager_{archetypeManager} {}

void ScriptExecutionSystem::Run(Registry::Ptr r,
                                zipper<scripting::components::ScriptPool> components) {
  const auto start = components.begin();
  const auto end = components.end();
  for (auto it = start; it != end; ++it) {
    auto&& [index, extractedComponents] = ~it;
    auto&& [scripts] = extractedComponents;
    currentScriptIndex_ = index;
    ProcessScriptPool(r, &scripts);
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
  return {registry, deltaTime_, registry->EntityFromIndex(currentScriptIndex_), archetypeManager_};
}

void ScriptExecutionSystem::HandleCollisionCallback(
    Registry::Const_Ptr registry,
    const std::shared_ptr<scripting::components::MonoBehaviour>& script,
    types::ScriptingContext::ConstPtr context) const {
  zygarde::Entity entity = registry->EntityFromIndex(currentScriptIndex_);
  auto collider = registry->GetComponent<physics::components::BoxCollider2D>(entity);
  if (!collider.has_value() || !collider.value()) {
    return;
  }
  while ((*collider)->HasCollision()) {
    auto collision = (*collider)->GetNextCollision();
    script->OnCollisionEnter(context, collision);
  }
}
