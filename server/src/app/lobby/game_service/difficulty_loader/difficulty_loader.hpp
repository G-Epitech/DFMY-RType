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

  std::vector<Difficulty> Run(const std::string &directory_path);

 private:
  void LoadDifficultyData(const nlohmann::json &jsonData);

  static void LoadDifficultyMetadata(const nlohmann::json &jsonData, Difficulty *difficulty);

  static void LoadDifficultyMultipliers(const nlohmann::json &jsonData, Difficulty *difficulty);
  static void LoadDifficultyPlayerMultipliers(const nlohmann::json &jsonData, Difficulty *difficulty);
  static void LoadDifficultyEnemyMultipliers(const nlohmann::json &jsonData, Difficulty *difficulty);

 private:
  std::string currentDirectory_;
  std::vector<Difficulty> difficulties_;
};
}  // namespace rtype::server::game
