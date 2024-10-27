/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "./archetype_loader/archetype_loader.hpp"
#include "api.hpp"
#include "entity.hpp"
#include "registry.hpp"
#include "scripting/types/mono_behaviour.hpp"

namespace zygarde::core::archetypes {
class EXPORT_ZYGARDE_API ArchetypeManager final {
 public:
  ArchetypeManager() = default;
  ~ArchetypeManager() = default;

 public:
  void LoadArchetypes(std::vector<std::string> directories,
                      const scripting::types::ScriptsMap& scriptsRegistry);

  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

 private:
  std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> archetypes_;
};
}  // namespace zygarde::core::archetypes
