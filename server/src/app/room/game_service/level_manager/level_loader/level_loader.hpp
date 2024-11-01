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

  /**
   * @brief Run the level level_loader
   * @param directory_path Directory path to load the levels from
   * @return A vector of levels
   */
  std::vector<Level> Run(const std::string &directory_path);

 private:
  /**
   * @brief Load level data from a JSON object
   * @param jsonData JSON object to load the level data from
   */
  void LoadLevelData(const nlohmann::json &jsonData);

  /**
   * @brief Load a level metadata from a JSON object (name, description, etc.)
   * @param jsonData JSON object to load the metadata from
   * @param level Level to load the metadata into
   */
  static void LoadLevelMetadata(const nlohmann::json &jsonData, Level *level);

  /**
   * @brief Load level wave data from a JSON object
   * @param jsonData JSON object to load the wave data from
   * @param level Level to load the wave data into
   */
  static void LoadLevelWaveData(const nlohmann::json &jsonData, Level *level);

  /**
   * @brief Load wave time data from a JSON object
   * @param jsonData JSON object to load the time data from
   * @param wave Wave to load the time data into
   */
  static void LoadLevelWaveTimeData(const nlohmann::json &jsonData, Wave *wave);

  /**
   * @brief Load wave enemy data from a JSON object
   * @param jsonData JSON object to load the enemy data from
   * @param wave Wave to load the enemy data into
   */
  static void LoadLevelWaveEnemyData(const nlohmann::json &jsonData, Wave *wave);

 private:
  /// @brief Levels loaded from the JSON files
  std::vector<Level> levels_;
};
}  // namespace rtype::server::game
