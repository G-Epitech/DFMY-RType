/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_loader.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "app/lobby/game_service/scripts/scripts_registry.hpp"
#include "zygarde/src/entity.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/scripting/types/context.hpp"

namespace rtype::server::tools {
class ArchetypeLoader {
 public:
  using RegistryAttachCallback =
      std::function<void(zygarde::Entity, const std::shared_ptr<zygarde::Registry>&)>;

  using ComponentParserFunction =
      std::function<void(std::vector<RegistryAttachCallback>*, const nlohmann::json&)>;

 public:
  ArchetypeLoader();
  ~ArchetypeLoader() = default;

  std::map<std::string, std::vector<RegistryAttachCallback>> Run();

 private:
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory);

  void LoadArchetypeJSON(const std::string& filePath);

  std::vector<RegistryAttachCallback> LoadArchetypeComponents(const nlohmann::json& jsonData);

  template <typename Component>
  static void EmplaceRegistryAttachCallback(std::vector<RegistryAttachCallback>* callbacks,
                                            Component&& component);

  void LoadArchetype(nlohmann::json jsonData);

 private:
  std::string currentPath_;
  std::map<std::string, std::vector<RegistryAttachCallback>> archetypes_;
  std::unordered_map<std::string, ComponentParserFunction> componentParsers_;
  std::shared_ptr<game::scripts::ScriptsRegistry> scriptsRegistry_;
};
}  // namespace rtype::server::tools

#include "archetype_loader.tpp"
