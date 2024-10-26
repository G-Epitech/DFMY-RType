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
  using RegistryAttachCallback =
      std::function<void(zygarde::Entity, const std::shared_ptr<zygarde::Registry>&)>;

  using ComponentParserFunction =
      std::function<void(std::vector<RegistryAttachCallback>*, const nlohmann::json&)>;

 public:
  ArchetypeManager();
  ~ArchetypeManager() = default;

  void LoadArchetypes();

  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

 private:
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory,
                                   const std::function<void(const nlohmann::json&)>& callback);

  static void LoadArchetypeJSON(const std::string& filePath,
                                const std::function<void(const nlohmann::json&)>& callback);

  std::vector<RegistryAttachCallback> LoadArchetypeComponents(const nlohmann::json& jsonData);

  template <typename Component>
  static void EmplaceRegistryAttachCallback(std::vector<RegistryAttachCallback>* callbacks,
                                            Component&& component);

  void LoadPlayerArchetype(nlohmann::json jsonData);
  static RegistryAttachCallback GetPlayerScript(nlohmann::json jsonData);

 private:
  std::string currentPath_;
  std::map<std::string, std::vector<RegistryAttachCallback>> archetypes_;
  std::unordered_map<std::string, ComponentParserFunction> componentParsers_;
};
}  // namespace rtype::server::tools

#include "archetype_manager.tpp"
