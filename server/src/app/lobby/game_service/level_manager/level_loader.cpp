/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LevelLoader.cpp
*/

#include "level_loader.hpp"

#include <filesystem>
#include <fstream>

using namespace rtype::server::game;

namespace fs = std::filesystem;

LevelLoader::LevelLoader() : currentDirectory_(fs::current_path().string()), levels_() {}

std::vector<Level> LevelLoader::LoadLevels(const std::string& directory_path) {
  std::string levelDirectoryPath = currentDirectory_ + directory_path;
  if (!fs::is_directory(levelDirectoryPath)) {
    throw std::runtime_error("Provided path is not a directory!");
  }

  for (const auto& entry : fs::directory_iterator(levelDirectoryPath)) {
    if (entry.is_regular_file()) {
      const auto& filePath = entry.path();
      if (filePath.extension() == ".json") {
        LoadLevelJSON(filePath.string());
      }
    }
  }
  return levels_;
}

void LevelLoader::LoadLevelJSON(const std::string& file_path) {
  std::ifstream inputFile(file_path);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Could not open the file: " + file_path);
  }

  nlohmann::json jsonData;
  try {
    inputFile >> jsonData;
  } catch (const nlohmann::json::parse_error& e) {
    inputFile.close();
    throw std::runtime_error("Could not parse the file: " + file_path);
  }
  inputFile.close();
  LoadLevelData(jsonData);
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
