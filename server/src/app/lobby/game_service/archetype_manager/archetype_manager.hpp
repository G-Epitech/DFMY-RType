/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "app/lobby/game_service/scripts/scripts_registry.hpp"
#include "archetype_loader/archetype_loader.hpp"
#include "zygarde/src/entity.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/scripting/types/context.hpp"

namespace rtype::server::tools {
class ArchetypeManager final {
 public:
  ArchetypeManager() = default;
  ~ArchetypeManager() = default;

 public:
  void LoadArchetypes();

  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

 private:
  std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> archetypes_;
};
}  // namespace rtype::server::tools
