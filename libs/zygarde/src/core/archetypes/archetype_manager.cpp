/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.cpp
*/

#include "archetype_manager.hpp"

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

void ArchetypeManager::LoadArchetypes(std::vector<std::string> directories,
                                      const scripting::types::ScriptsMap& scriptsRegistry) {
  ArchetypeLoader archetypeLoader(std::move(directories), scriptsRegistry);

  archetypes_ = archetypeLoader.Run();
}
