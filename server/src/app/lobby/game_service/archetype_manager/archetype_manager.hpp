/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "libs/game/src/types/game_entities.hpp"
#include "zygarde/src/entity.hpp"
#include "zygarde/src/registry.hpp"

namespace rtype::server::tools {
class ArchetypeManager final {
  using RegistryAddFunction =
      std::function<void(zygarde::Entity, const std::shared_ptr<zygarde::Registry>&)>;

 public:
  ArchetypeManager();
  ~ArchetypeManager() = default;

  void LoadArchetypes();

  void InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                       const std::string& archetype_name,
                       rtype::sdk::game::types::GameEntityType type);

 private:
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory,
                                   const std::function<void(const nlohmann::json&)>& callback);
  void LoadPlayerArchetype(nlohmann::json jsonData);

 private:
  std::string currentPath_;
  std::map<std::string, std::vector<RegistryAddFunction>> playerArchetypes_;
  std::map<std::string, std::vector<RegistryAddFunction>> powerupArchetypes_;
  std::map<std::string, std::vector<RegistryAddFunction>> enemyArchetypes_;
  std::map<std::string, std::vector<RegistryAddFunction>> projectileArchetypes_;
};
}  // namespace rtype::server::tools
