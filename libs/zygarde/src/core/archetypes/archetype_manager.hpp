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

namespace zygarde::core::archetypes {
class EXPORT_ZYGARDE_API ArchetypeManager final {
 public:
  ArchetypeManager() = default;
  ~ArchetypeManager() = default;

 public:
  /**
   * @brief Load archetypes from directories
   * @param directories Directories to load archetypes from
   * @param scriptsRegistry Registry of scripts containing script names and their constructors
   */
  void LoadArchetypes(std::vector<std::string> directories,
                      const scripting::types::ScriptsMap& scriptsRegistry);

  /**
   * @brief Invoke an archetype by name
   * @param registry Registry to attach the archetype to
   * @param archetype_name Name of the archetype to invoke
   * @return Entity of the invoked archetype
   */
  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

 private:
  /// @brief Archetype map
  std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> archetypes_;
};
}  // namespace zygarde::core::archetypes
