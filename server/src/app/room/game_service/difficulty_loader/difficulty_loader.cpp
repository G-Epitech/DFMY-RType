/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** DifficultyLoader.cpp
*/

#include "difficulty_loader.hpp"

#include <fstream>

#include "utils/json_helper/json_helper.hpp"

using namespace rtype::server::game;

DifficultyLoader::DifficultyLoader() : difficulties_() {}

void DifficultyLoader::Run(const std::string& directory_path) {
  std::vector<nlohmann::json> jsonDifficulties =
      utils::JsonHelper::ReadJsonFilesFromDirectory(directory_path);

  for (const auto& jsonDifficulty : jsonDifficulties) {
    LoadDifficultyData(jsonDifficulty);
  }
}

void DifficultyLoader::LoadDifficultyData(const nlohmann::json& jsonData) {
  DifficultyData difficulty;

  LoadDifficultyMetadata(jsonData, &difficulty);
  LoadDifficultyMultipliers(jsonData, &difficulty);
  difficulties_.push_back(difficulty);
}

void DifficultyLoader::LoadDifficultyMetadata(const nlohmann::json& jsonData,
                                              DifficultyData* difficulty) {
  if (jsonData.contains("difficulty")) {
    difficulty->name = jsonData["difficulty"];
  } else {
    difficulty->name = "Unknown";
  }
  if (jsonData.contains("description")) {
    difficulty->description = jsonData["description"];
  } else {
    difficulty->description = "No description";
  }
}

void DifficultyLoader::LoadDifficultyMultipliers(const nlohmann::json& jsonData,
                                                 DifficultyData* difficulty) {
  if (jsonData.contains("multipliers")) {
    LoadDifficultyPlayerMultipliers(jsonData["multipliers"], difficulty);
    LoadDifficultyEnemyMultipliers(jsonData["multipliers"], difficulty);
  }
}

void DifficultyLoader::LoadDifficultyPlayerMultipliers(const nlohmann::json& jsonData,
                                                       DifficultyData* difficulty) {
  if (!jsonData.contains("player")) {
    return;
  }
  const auto& player = jsonData["player"];

  difficulty->multipliers.player.health =
      player.contains("health") ? player["health"].get<float>() : 1.0f;
  difficulty->multipliers.player.speed =
      player.contains("speed") ? player["speed"].get<float>() : 1.0f;
  difficulty->multipliers.player.fireRate =
      player.contains("fireRate") ? player["fireRate"].get<float>() : 1.0f;
  difficulty->multipliers.player.damage =
      player.contains("damage") ? player["damage"].get<float>() : 1.0f;
}

void DifficultyLoader::LoadDifficultyEnemyMultipliers(const nlohmann::json& jsonData,
                                                      DifficultyData* difficulty) {
  if (!jsonData.contains("enemy")) {
    return;
  }
  const auto& enemy = jsonData["enemy"];

  difficulty->multipliers.enemy.health =
      enemy.contains("health") ? enemy["health"].get<float>() : 1.0f;
  difficulty->multipliers.enemy.speed =
      enemy.contains("speed") ? enemy["speed"].get<float>() : 1.0f;
  difficulty->multipliers.enemy.fireRate =
      enemy.contains("fireRate") ? enemy["fireRate"].get<float>() : 1.0f;
  difficulty->multipliers.enemy.damage =
      enemy.contains("damage") ? enemy["damage"].get<float>() : 1.0f;
}

DifficultyData DifficultyLoader::GetDifficultyByType(
    rtype::sdk::game::types::Difficulty difficultyType) const {
  auto name = difficultiesMap_[difficultyType];
  for (const auto& difficulty : difficulties_) {
    if (difficulty.name == name) {
      return difficulty;
    }
  }
  return difficulties_[0];
}
