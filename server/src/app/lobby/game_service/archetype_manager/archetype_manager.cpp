/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.cpp
*/

#include "archetype_manager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "app/lobby/filepaths.hpp"
#include "app/lobby/game_service/archetype_manager/component_parser/component_parser.hpp"
#include "app/lobby/game_service/scripts/player_script.hpp"

using namespace rtype::server::tools;

namespace fs = std::filesystem;

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

void ArchetypeManager::LoadArchetypes() {
  ArchetypeLoader archetypeLoader;

  archetypes_ = archetypeLoader.Run();
}
