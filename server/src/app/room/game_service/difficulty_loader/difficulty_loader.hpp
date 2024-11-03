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

#include "libs/game/src/types/difficulties.hpp"
#include "types/difficulty_data.hpp"

namespace rtype::server::game {
class DifficultyLoader final {
 public:
  DifficultyLoader();
  ~DifficultyLoader() = default;

  /**
   * @brief Run the difficulty level_loader
   * @param directory_path Directory path to load the difficulties from
   * @return A vector of difficulties
   */
  void Run(const std::string &directory_path);

  /**
   * @brief Get the difficulties
   * @return A vector of difficulties
   */
  [[nodiscard]] const std::vector<DifficultyData> &GetDifficulties() const { return difficulties_; }

  /**
   * @brief Get a difficulty by its type
   * @param difficultyType DifficultyData type
   * @return The difficulty data
   */
  [[nodiscard]] DifficultyData GetDifficultyByType(
      rtype::sdk::game::types::Difficulty difficultyType) const;

 private:
  /**
   * @brief Load difficulty data from a JSON object
   * @param jsonData JSON object to load the difficulty data from
   */
  void LoadDifficultyData(const nlohmann::json &jsonData);

  /**
   * @brief Load a difficulty metadata from a JSON object (name, description, etc.)
   * @param jsonData JSON object to load the metadata from
   * @param difficulty DifficultyData to load the metadata into
   */
  static void LoadDifficultyMetadata(const nlohmann::json &jsonData, DifficultyData *difficulty);

  /**
   * @brief Load difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the multipliers from
   * @param difficulty DifficultyData to load the multipliers into
   */
  static void LoadDifficultyMultipliers(const nlohmann::json &jsonData, DifficultyData *difficulty);

  /**
   * @brief Load player difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the player multipliers from
   * @param difficulty DifficultyData to load the player multipliers into
   */
  static void LoadDifficultyPlayerMultipliers(const nlohmann::json &jsonData,
                                              DifficultyData *difficulty);

  /**
   * @brief Load enemy difficulty multipliers from a JSON object
   * @param jsonData JSON object to load the enemy multipliers from
   * @param difficulty DifficultyData to load the enemy multipliers into
   */
  static void LoadDifficultyEnemyMultipliers(const nlohmann::json &jsonData,
                                             DifficultyData *difficulty);

 private:
  /// @brief Vector of difficulties
  std::vector<DifficultyData> difficulties_;

  /// @brief Map of difficulty names
  static inline std::map<rtype::sdk::game::types::Difficulty, std::string> difficultiesMap_ = {
      {rtype::sdk::game::types::Difficulty::kEasy, "easy"},
      {rtype::sdk::game::types::Difficulty::kDefault, "default"},
      {rtype::sdk::game::types::Difficulty::kMedium, "medium"},
      {rtype::sdk::game::types::Difficulty::kHard, "hard"},
      {rtype::sdk::game::types::Difficulty::kInsane, "insane"},
  };
};
}  // namespace rtype::server::game
