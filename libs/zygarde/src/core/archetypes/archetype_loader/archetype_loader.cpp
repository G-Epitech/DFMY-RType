/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_loader.cpp
*/

#include "archetype_loader.hpp"

#include <fstream>
#include <utility>

#include "core/archetypes/component_parser/component_parser.hpp"

using namespace zygarde::core::archetypes;

namespace fs = std::filesystem;

ArchetypeLoader::ArchetypeLoader(std::string archetype_directory,
                                 const scripting::types::ScriptsMap& scriptsRegistry)
    : archetypes_(), componentParsers_(), archetypeDirectory_(std::move(archetype_directory)) {
  InitializeComponentParsers(scriptsRegistry);
}

std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> ArchetypeLoader::Run() {
  LoadArchetypesFromDirectory(archetypeDirectory_);
  return archetypes_;
}

void ArchetypeLoader::LoadArchetypesFromDirectory(const std::string& archetypeDirectory) {
  fs::path directoryPath = fs::current_path().string() + archetypeDirectory;

  if (!fs::exists(directoryPath)) {
    throw std::runtime_error("Provided path does not exist: " + directoryPath.string());
  }

  if (!fs::is_directory(directoryPath)) {
    throw std::runtime_error("Provided path is not a directory: " + directoryPath.string());
  }

  for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
    if (entry.is_regular_file() && entry.path().extension() == ".json") {
      LoadArchetypeJSON(entry.path().string());
    }
  }
}

void ArchetypeLoader::LoadArchetypeJSON(const std::string& filePath) {
  std::ifstream inputFile(filePath);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Could not open the file: " + filePath);
  }

  nlohmann::json jsonData;
  try {
    inputFile >> jsonData;
  } catch (const nlohmann::json::parse_error& e) {
    inputFile.close();
    throw std::runtime_error("Could not parse the file: " + filePath);
  }
  inputFile.close();
  LoadArchetype(jsonData);
}

void ArchetypeLoader::LoadArchetype(nlohmann::json jsonData) {
  const auto& archetypeName = jsonData["archetype_name"].get<std::string>();

  archetypes_[archetypeName] = LoadArchetypeComponents(jsonData);
}

std::vector<ArchetypeLoader::RegistryAttachCallback> ArchetypeLoader::LoadArchetypeComponents(
    const nlohmann::json& jsonData) {
  std::vector<RegistryAttachCallback> components;

  if (!jsonData.contains("components")) {
    return components;
  }

  const auto& componentsJson = jsonData["components"];
  for (const auto& component : componentsJson) {
    const auto& componentName = component["name"].get<std::string>();
    auto it = componentParsers_.find(componentName);
    if (it != componentParsers_.end()) {
      it->second(&components, component);
    } else {
      throw std::runtime_error("Component parser not found: " + componentName);
    }
  }
  return components;
}

void ArchetypeLoader::InitializeComponentParsers(
    const scripting::types::ScriptsMap& scriptsRegistry) {
  componentParsers_ = {
      {"position",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& json) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParsePosition(json));
       }},
      {"rigidbody2d",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& json) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseRigidbody2D(json));
       }},
      {"box_collider2d",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& json) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseBoxCollider2D(json));
       }},
      {"tags",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& json) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseTags(json));
       }},
      {"script_pool", [scriptsRegistry](std::vector<RegistryAttachCallback>* callbacks,
                                        const nlohmann::json& component) {
         const auto& map = ComponentParser::ParseScriptPoolData(component);

         callbacks->emplace_back(
             [scriptsRegistry, map](const zygarde::Entity& entity,
                                    const std::shared_ptr<zygarde::Registry>& registry) {
               std::list<std::shared_ptr<scripting::components::MonoBehaviour>> scripts;

               for (const auto& [scriptName, valuesMap] : map) {
                 auto script = scriptsRegistry.at(scriptName)();
                 script->OnEnable(valuesMap);
                 scripts.push_back(script);
               }

               registry->AddComponent<scripting::components::ScriptPool>(
                   entity, scripting::components::ScriptPool(scripts));
             });
       }}};
}
