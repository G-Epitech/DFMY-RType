/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_loader.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "api.hpp"
#include "entity.hpp"
#include "registry.hpp"
#include "scripting/types/mono_behaviour.hpp"
#include "scripting/types/values_map.hpp"

namespace zygarde::core::archetypes {
class EXPORT_ZYGARDE_API ArchetypeLoader final {
 public:
  using RegistryAttachCallback =
      std::function<void(zygarde::Entity, const std::shared_ptr<zygarde::Registry>&)>;

  using ComponentParserFunction = std::function<void(
      std::vector<ArchetypeLoader::RegistryAttachCallback>*, const nlohmann::json&)>;

 public:
  ArchetypeLoader(std::vector<std::string> directories,
                  const scripting::types::ScriptsMap& scriptsRegistry);
  ~ArchetypeLoader() = default;

  std::map<std::string, std::vector<RegistryAttachCallback>> Run();

 private:
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory);

  void LoadArchetypeJSON(const std::string& filePath);

  std::vector<RegistryAttachCallback> LoadArchetypeComponents(const nlohmann::json& jsonData);

  template <typename Component>
  static void EmplaceRegistryAttachCallback(std::vector<RegistryAttachCallback>* callbacks,
                                            Component component);

  void LoadArchetype(nlohmann::json jsonData);

 private:
  std::string currentPath_;
  std::map<std::string, std::vector<RegistryAttachCallback>> archetypes_;
  std::unordered_map<std::string, ComponentParserFunction> componentParsers_;
  std::vector<std::string> directories_;
};
}  // namespace zygarde::core::archetypes

#include "archetype_loader.tpp"
