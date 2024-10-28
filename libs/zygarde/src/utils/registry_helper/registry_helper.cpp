/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** RegistryHelper.cpp
*/

#include "./registry_helper.hpp"

#include "core/components/components.hpp"
#include "physics/2d/components/components.hpp"
#include "physics/2d/systems/position/position_system.hpp"
#include "physics/2d/systems/systems.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripting/systems/execution/script_execution_system.hpp"

using namespace zygarde::utils;

void RegistryHelper::RegisterBaseComponents(const std::shared_ptr<Registry> &registry) {
  RegisterCoreComponents(registry);
  RegisterPhysicsComponents(registry);
  RegisterScriptingComponents(registry);
}

void RegistryHelper::RegisterCoreComponents(const std::shared_ptr<Registry> &registry) {
  registry->RegisterComponent<core::components::Transform>();
  registry->RegisterComponent<core::components::Position>();
  registry->RegisterComponent<core::components::Tags>();
}

void RegistryHelper::RegisterPhysicsComponents(const std::shared_ptr<Registry> &registry) {
  registry->RegisterComponent<physics::components::BoxCollider2D>();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
}

void RegistryHelper::RegisterScriptingComponents(const std::shared_ptr<Registry> &registry) {
  registry->RegisterComponent<scripting::components::ScriptPool>();
}

void RegistryHelper::RegisterBaseSystems(
    const std::shared_ptr<Registry> &registry, const Timer::Nanoseconds &delta_time,
    const std::shared_ptr<core::archetypes::ArchetypeManager> &archetypeManager) {
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  registry->AddSystem<physics::systems::CollisionSystem>();
  registry->AddSystem<physics::systems::PositionSystem>();
  registry->AddSystem<scripting::systems::ScriptExecutionSystem>(delta_time, archetypeManager);
}
