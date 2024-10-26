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
  std::cout << "Current path: " << currentPath_ << std::endl;
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
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
          throw std::runtime_error("Could not open the file: " + filePath.string());
        }

        nlohmann::json jsonData;
        try {
          inputFile >> jsonData;
          std::cout << "Successfully read: " << filePath.filename() << "\n";
        } catch (const nlohmann::json::parse_error& e) {
          inputFile.close();
          throw std::runtime_error("Could not parse the file: " + filePath.string());
        }
        inputFile.close();
        callback(jsonData);
      }
    }
  }
}

std::vector<ArchetypeManager::RegistryAddFunction> ArchetypeManager::LoadArchetypeComponents(
    const nlohmann::json& jsonData) {
  std::vector<RegistryAddFunction> components;
  const auto& componentsJson = jsonData["components"];

  for (const auto& component : componentsJson) {
    const auto& componentName = component["name"].get<std::string>();
    if (componentName == "position") {
      auto position = ComponentParser::ParsePosition(component);
      components.emplace_back(
          [position](zygarde::Entity entity, const std::shared_ptr<zygarde::Registry>& registry) {
            registry->AddComponent<zygarde::core::components::Position>(
                entity, zygarde::core::components::Position(position));
          });
    }
    if (componentName == "rigidbody2d") {
      auto rigidbody2d = ComponentParser::ParseRigidbody2D(component);
      components.emplace_back([rigidbody2d](zygarde::Entity entity,
                                            const std::shared_ptr<zygarde::Registry>& registry) {
        registry->AddComponent<zygarde::physics::components::Rigidbody2D>(
            entity, zygarde::physics::components::Rigidbody2D(rigidbody2d));
      });
    }
    if (componentName == "box_collider2d") {
      auto boxCollider2d = ComponentParser::ParseBoxCollider2D(component);
      components.emplace_back([boxCollider2d](zygarde::Entity entity,
                                              const std::shared_ptr<zygarde::Registry>& registry) {
        registry->AddComponent<zygarde::physics::components::BoxCollider2D>(
            entity, zygarde::physics::components::BoxCollider2D(boxCollider2d));
      });
    }
    if (componentName == "tags") {
      auto tags = ComponentParser::ParseTags(component);
      components.emplace_back(
          [tags](zygarde::Entity entity, const std::shared_ptr<zygarde::Registry>& registry) {
            registry->AddComponent<zygarde::core::components::Tags>(
                entity, zygarde::core::components::Tags(tags));
          });
    }
  }
  return components;
}

void ArchetypeManager::LoadPlayerArchetype(nlohmann::json jsonData) {
  const auto& archetypeName = jsonData["archetype_name"].get<std::string>();

  if (!jsonData.contains("data") || !jsonData["data"].contains("class")) {
    throw std::runtime_error("Invalid player archetype: " + archetypeName);
  }
  std::vector<RegistryAddFunction> components = LoadArchetypeComponents(jsonData["data"]);
  components.push_back(GetPlayerScript(jsonData["data"]));
  archetypes_[archetypeName] = components;
}

ArchetypeManager::RegistryAddFunction ArchetypeManager::GetPlayerScript(nlohmann::json jsonData) {
  std::shared_ptr<game::scripts::PlayerScript> script =
      std::make_shared<game::scripts::PlayerScript>();
  game::scripts::PlayerScript::PlayerProps props;
  RegistryAddFunction scriptComponent;

  const auto& classData = jsonData["class"];
  props.health = classData["health"].get<float>();
  props.speed = classData["speed"].get<float>();
  props.className = classData["className"].get<std::string>();
  props.powerCooldown = classData["powerCooldown"].get<float>();
  props.primaryWeapon = classData["primaryWeapon"].get<std::string>();
  props.secondaryWeapon = classData["secondaryWeapon"].get<std::string>();
  script->SetPlayerProps(props);
  std::vector<std::shared_ptr<zygarde::scripting::components::MonoBehaviour>> scripts;
  scripts.push_back(script);
  scriptComponent = [scripts](zygarde::Entity entity,
                              const std::shared_ptr<zygarde::Registry>& registry) {
    registry->AddComponent<zygarde::scripting::components::ScriptPool>(
        entity, zygarde::scripting::components::ScriptPool{scripts});
  };
  return scriptComponent;
}
