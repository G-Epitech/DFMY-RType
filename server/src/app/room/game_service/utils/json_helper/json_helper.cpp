/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** JsonHelper.cpp
*/

#include "json_helper.hpp"

#include <filesystem>
#include <fstream>

using namespace rtype::server::game::utils;

namespace fs = std::filesystem;

std::vector<nlohmann::json> JsonHelper::ReadJsonFilesFromDirectory(
    const std::string& directory_path) {
  std::string currentDirectory = fs::current_path().string();
  std::string jsonDirectoryPath = currentDirectory + directory_path;
  std::vector<nlohmann::json> jsonFiles;

  if (!fs::is_directory(jsonDirectoryPath)) {
    throw std::runtime_error("Provided path is not a directory!");
  }

  for (const auto& entry : fs::directory_iterator(jsonDirectoryPath)) {
    if (entry.is_regular_file()) {
      const auto& filePath = entry.path();
      if (filePath.extension() == ".json") {
        jsonFiles.push_back(ReadJsonFile(filePath.string()));
      }
    }
  }
  return jsonFiles;
}

nlohmann::json JsonHelper::ReadJsonFile(const std::string& file_path) {
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
  return jsonData;
}
