/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

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

  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

 private:
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory,
                                   const std::function<void(const nlohmann::json&)>& callback);

  static std::vector<RegistryAddFunction> LoadArchetypeComponents(const nlohmann::json& jsonData);

  void LoadPlayerArchetype(nlohmann::json jsonData);
  static RegistryAddFunction GetPlayerScript(nlohmann::json jsonData);

 private:
  std::string currentPath_;
  std::map<std::string, std::vector<RegistryAddFunction>> archetypes_;
};
}  // namespace rtype::server::tools
