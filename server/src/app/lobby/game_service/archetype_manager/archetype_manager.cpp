/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.cpp
*/

#include "archetype_manager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "app/lobby/filepaths.hpp"
#include "app/lobby/game_service/archetype_manager/component_parser/component_parser.hpp"
#include "app/lobby/game_service/scripts/player_script.hpp"

using namespace rtype::server::tools;

namespace fs = std::filesystem;

ArchetypeManager::ArchetypeManager() {
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

zygarde::Entity ArchetypeManager::InvokeArchetype(
    const std::shared_ptr<zygarde::Registry>& registry, const std::string& archetype_name) {
  zygarde::Entity entity = registry->SpawnEntity();

  if (archetypes_.find(archetype_name) == archetypes_.end()) {
    throw std::runtime_error("Archetype not found: " + archetype_name);
  }
  for (const auto& component : archetypes_[archetype_name]) {
    component(entity, registry);
  }
  return entity;
}

void ArchetypeManager::LoadArchetypes() {
  LoadArchetypesFromDirectory(
      rtype::server::kPlayerArchetypesDirectory,
      [this](const nlohmann::json& jsonData) { LoadPlayerArchetype(jsonData); });
}

void ArchetypeManager::LoadArchetypesFromDirectory(
    const std::string& archetypeDirectory,
    const std::function<void(const nlohmann::json&)>& callback) {
  std::string directoryPath = currentPath_ + archetypeDirectory;
  if (!fs::is_directory(directoryPath)) {
    throw std::runtime_error("Provided path is not a directory!");
  }

  for (const auto& entry : fs::directory_iterator(directoryPath)) {
    if (entry.is_regular_file()) {
      const auto& filePath = entry.path();
      if (filePath.extension() == ".json") {
        LoadArchetypeJSON(filePath.string(), callback);
      }
    }
  }
}

void ArchetypeManager::LoadArchetypeJSON(
    const std::string& filePath, const std::function<void(const nlohmann::json&)>& callback) {
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
  callback(jsonData);
}

std::vector<ArchetypeManager::RegistryAttachCallback> ArchetypeManager::LoadArchetypeComponents(
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

void ArchetypeManager::LoadPlayerArchetype(nlohmann::json jsonData) {
  const auto& archetypeName = jsonData["archetype_name"].get<std::string>();

  archetypes_[archetypeName] = LoadArchetypeComponents(jsonData);
}
