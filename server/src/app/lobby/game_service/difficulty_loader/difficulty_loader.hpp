/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** DifficultyLoader.hpp
*/

#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "types/difficulty.hpp"

namespace rtype::server::game {
class DifficultyLoader {
 public:
  DifficultyLoader();
  ~DifficultyLoader() = default;

  /**
   * @brief Run the difficulty loader
   * @param directory_path Directory path to load the difficulties from
   * @return A vector of difficulties
   */
  std::vector<Difficulty> Run(const std::string &directory_path);

 private:
  /**
   * @brief Load difficulty data from a JSON object
   * @param jsonData JSON object to load the difficulty data from
   */
  void LoadDifficultyData(const nlohmann::json &jsonData);

  /**
   * @brief Load a difficulty metadata from a JSON object (name, description, etc.)
   * @param jsonData JSON object to load the metadata from
   * @param difficulty Difficulty to load the metadata into
   */
  static void LoadDifficultyMetadata(const nlohmann::json &jsonData, Difficulty *difficulty);

  /**
   * @brief Load difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the multipliers from
   * @param difficulty Difficulty to load the multipliers into
   */
  static void LoadDifficultyMultipliers(const nlohmann::json &jsonData, Difficulty *difficulty);

  /**
   * @brief Load player difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the player multipliers from
   * @param difficulty Difficulty to load the player multipliers into
   */
  static void LoadDifficultyPlayerMultipliers(const nlohmann::json &jsonData,
                                              Difficulty *difficulty);

  /**
   * @brief Load enemy difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the enemy multipliers from
   * @param difficulty Difficulty to load the enemy multipliers into
   */
  static void LoadDifficultyEnemyMultipliers(const nlohmann::json &jsonData,
                                             Difficulty *difficulty);

 private:
  /// @brief Vector of difficulties
  std::vector<Difficulty> difficulties_;
};
}  // namespace rtype::server::game
