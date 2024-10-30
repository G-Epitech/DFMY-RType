/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LevelLoader.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "types/level.hpp"

namespace rtype::server::game {
class LevelLoader {
 public:
  LevelLoader();
  ~LevelLoader() = default;

  std::vector<Level> Run(const std::string &directory_path);

 private:
  void LoadLevelData(const nlohmann::json &jsonData);

  static void LoadLevelMetadata(const nlohmann::json &jsonData, Level *level);

  static void LoadLevelWaveData(const nlohmann::json &jsonData, Level *level);

  static void LoadLevelWaveTimeData(const nlohmann::json &jsonData, Wave *wave);

  static void LoadLevelWaveEnemyData(const nlohmann::json &jsonData, Wave *wave);

 private:
  std::vector<Level> levels_;
};
}  // namespace rtype::server::game
