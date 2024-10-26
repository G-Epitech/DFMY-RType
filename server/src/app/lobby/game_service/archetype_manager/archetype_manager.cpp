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

using namespace rtype::server::tools;

namespace fs = std::filesystem;

ArchetypeManager::ArchetypeManager() {
  currentPath_ = std::filesystem::current_path().string();
  std::cout << "Current path: " << currentPath_ << std::endl;
}

void ArchetypeManager::InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                       const std::string& archetype_name,
                                       rtype::sdk::game::types::GameEntityType type) {}

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

void ArchetypeManager::LoadPlayerArchetype(nlohmann::json jsonData) {
  const auto& archetypeName = jsonData["archetype_name"].get<std::string>();
  const auto& components = jsonData["data"]["components"];

  for (const auto& component : components) {
    const auto& componentName = component["name"].get<std::string>();
    std::cout << "Component name: " << componentName << "\n";
  }
}
