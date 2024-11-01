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
  /// @brief Callback function to attach a component to an entity
  using RegistryAttachCallback =
      std::function<void(zygarde::Entity, const std::shared_ptr<zygarde::Registry>&)>;

  /// @brief Function to parse a component from a json object
  using ComponentParserFunction = std::function<void(
      std::vector<ArchetypeLoader::RegistryAttachCallback>*, const nlohmann::json&)>;

 public:
  /**
   * @brief Construct a new Archetype Loader object
   * @param directories Directories to load archetypes from
   * @param scriptsRegistry Registry of scripts containing script names and their constructors
   */
  ArchetypeLoader(std::string archetype_directory,
                  const scripting::types::ScriptsMap& scriptsRegistry);

  ~ArchetypeLoader() = default;

  /**
   * Run the archetype loader
   * @return A map of archetype names to a vector of attach callbacks
   */
  std::map<std::string, std::vector<RegistryAttachCallback>> Run();

 private:
  /**
   * @brief Load archetypes from a directory
   * @param archetypeDirectory Directory to load archetypes from
   */
  void LoadArchetypesFromDirectory(const std::string& archetypeDirectory);

  /**
   * @brief Load an archetype from a JSON file
   * @param filePath Path to the JSON file
   */
  void LoadArchetypeJSON(const std::string& filePath);

  /**
   * @brief Load an archetype from a JSON object
   * @param jsonData JSON object to load the archetype from
   */
  void LoadArchetype(nlohmann::json jsonData);

  /**
   * @brief Load components from a JSON object
   * @param jsonData JSON object to load components from
   * @return A vector of attach callbacks
   */
  std::vector<RegistryAttachCallback> LoadArchetypeComponents(const nlohmann::json& jsonData);

  /**
   * @brief Emplace a registry attach callback
   * @tparam Component Type of component to attach
   * @param callbacks Callbacks that will add the component to an entity
   * @param component Component to attach
   */
  template <typename Component>
  static void EmplaceRegistryAttachCallback(std::vector<RegistryAttachCallback>* callbacks,
                                            Component component);

  /**
   * @brief Initialize component parsers
   */
  void InitializeComponentParsers(const scripting::types::ScriptsMap& scriptsRegistry);

 private:
  /// @brief Archetypes map
  std::map<std::string, std::vector<RegistryAttachCallback>> archetypes_;
  /// @brief Map of component parsers
  std::unordered_map<std::string, ComponentParserFunction> componentParsers_;
  /// @brief Array of directories to load archetypes from
  std::string archetypeDirectory_;
};
}  // namespace zygarde::core::archetypes

#include "archetype_loader.tpp"
