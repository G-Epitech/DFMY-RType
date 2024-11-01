/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.cpp
*/

#include "archetype_manager.hpp"

#include <iostream>
#include <utility>

using namespace zygarde::core::archetypes;

zygarde::Entity ArchetypeManager::InvokeArchetype(
    const std::shared_ptr<zygarde::Registry>& registry, const std::string& archetype_name) {
  zygarde::Entity entity = registry->SpawnEntity();

  if (archetypes_.find(archetype_name) == archetypes_.end()) {
    throw std::runtime_error("Archetype not found: " + archetype_name);
  }
  for (const auto& component : archetypes_[archetype_name]) {
    component(entity, registry);
  }
  return entity;
}

void ArchetypeManager::LoadArchetypes(const std::string& archetype_directory,
                                      const scripting::types::ScriptsMap& scriptsRegistry) {
  ArchetypeLoader archetypeLoader(archetype_directory, scriptsRegistry);

  archetypes_ = archetypeLoader.Run();
  for (const auto& [name, components] : archetypes_) {
    std::cout << "Loaded archetype: " << name << std::endl;
  }
}

void ArchetypeManager::ScheduleInvocation(
    const ArchetypeManager::ScheduleInvocationParams& params) {
  invokationQueue_.push_back(params);
}

void ArchetypeManager::ExecuteScheduledInvocations(
    const std::shared_ptr<zygarde::Registry>& registry) {
  for (const auto& params : invokationQueue_) {
    auto spawnedEntity = InvokeArchetype(registry, params.archetypeName);
    params.registryAttachCallback(registry, spawnedEntity);
  }
  invokationQueue_.clear();
}
