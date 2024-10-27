/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_loader.cpp
*/

#include "archetype_loader.hpp"

#include <fstream>

#include "app/lobby/filepaths.hpp"
#include "app/lobby/game_service/archetype_manager/component_parser/component_parser.hpp"

using namespace rtype::server::tools;

namespace fs = std::filesystem;

ArchetypeLoader::ArchetypeLoader() {
  currentPath_ = std::filesystem::current_path().string();
  scriptsRegistry_ = std::make_shared<game::scripts::ScriptsRegistry>();
  componentParsers_ = {
      {"position",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& component) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParsePosition(component));
       }},
      {"rigidbody2d",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& component) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseRigidbody2D(component));
       }},
      {"box_collider2d",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& component) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseBoxCollider2D(component));
       }},
      {"tags",
       [](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& component) {
         EmplaceRegistryAttachCallback(callbacks, ComponentParser::ParseTags(component));
       }},
      {
          "script_pool",
          [this](std::vector<RegistryAttachCallback>* callbacks, const nlohmann::json& component) {
            const auto& map = ComponentParser::ParseScriptPoolData(component);
            std::vector<std::shared_ptr<scripting::components::MonoBehaviour>> scripts;
            for (const auto& [scriptName, valuesMap] : map) {
              auto script = scriptsRegistry_->GetScript(scriptName);
              script->onEnable(valuesMap);
              scripts.push_back(script);
            }
            EmplaceRegistryAttachCallback(callbacks, scripting::components::ScriptPool(scripts));
          },
      }};
}

std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> ArchetypeLoader::Run() {
  LoadArchetypesFromDirectory(rtype::server::kPlayerArchetypesDirectory);
  LoadArchetypesFromDirectory(rtype::server::kEnemyArchetypesDirectory);
  LoadArchetypesFromDirectory(rtype::server::kProjectileArchetypesDirectory);
  return archetypes_;
}

void ArchetypeLoader::LoadArchetypesFromDirectory(const std::string& archetypeDirectory) {
  std::string directoryPath = currentPath_ + archetypeDirectory;
  if (!fs::is_directory(directoryPath)) {
    throw std::runtime_error("Provided path is not a directory!");
  }

  for (const auto& entry : fs::directory_iterator(directoryPath)) {
    if (entry.is_regular_file()) {
      const auto& filePath = entry.path();
      if (filePath.extension() == ".json") {
        LoadArchetypeJSON(filePath.string());
      }
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
