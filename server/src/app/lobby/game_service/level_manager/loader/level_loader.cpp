/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LevelLoader.cpp
*/

#include "level_loader.hpp"

#include <filesystem>

#include "utils/json_helper/json_helper.hpp"

using namespace rtype::server::game;

LevelLoader::LevelLoader() : levels_() {}

std::vector<Level> LevelLoader::Run(const std::string& directory_path) {
  std::vector<nlohmann::json> jsonFiles =
      utils::JsonHelper::ReadJsonFilesFromDirectory(directory_path);

  for (const auto& jsonFile : jsonFiles) {
    LoadLevelData(jsonFile);
  }
  return levels_;
}

void LevelLoader::LoadLevelData(const nlohmann::json& jsonData) {
  Level level;

  LoadLevelMetadata(jsonData, &level);
  LoadLevelWaveData(jsonData, &level);
  levels_.push_back(level);
}

void LevelLoader::LoadLevelMetadata(const nlohmann::json& jsonData, Level* level) {
  if (jsonData.contains("name")) {
    level->name = jsonData["name"].get<std::string>();
  } else {
    level->name = "Unknown";
  }
  if (jsonData.contains("description")) {
    level->description = jsonData["description"].get<std::string>();
  } else {
    level->description = "No description";
  }
}

void LevelLoader::LoadLevelWaveData(const nlohmann::json& jsonData, Level* level) {
  if (!jsonData.contains("waves")) {
    throw std::runtime_error("Level does not contain any waves!");
  }

  for (const auto& waveData : jsonData["waves"]) {
    Wave wave;

    LoadLevelWaveTimeData(waveData, &wave);
    LoadLevelWaveEnemyData(waveData, &wave);
    level->waves.push_back(wave);
  }
}

void LevelLoader::LoadLevelWaveTimeData(const nlohmann::json& jsonData, Wave* wave) {
  wave->maxTime =
      jsonData.contains("maxTime") ? wave->maxTime = jsonData["maxTime"].get<float>() : 30.0f;
}

void LevelLoader::LoadLevelWaveEnemyData(const nlohmann::json& jsonData, Wave* wave) {
  for (const auto& enemyData : jsonData["enemies"]) {
    WaveEnemy enemy;

    if (!enemyData.contains("name") || !enemyData.contains("count")) {
      throw std::runtime_error("Enemy data is missing name or count!");
    }
    enemy.name = enemyData["name"].get<std::string>();
    enemy.count = enemyData["count"].get<int>();
    wave->enemies.push_back(enemy);
  }
}
