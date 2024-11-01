/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** JsonHelper.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

namespace rtype::server::game::utils {
class JsonHelper {
 public:
  JsonHelper() = delete;
  ~JsonHelper() = delete;

  /**
   * @brief Read all JSON files from a directory
   * @param directory_path Directory path to read the JSON files from
   * @return A vector of JSON objects
   */
  [[nodiscard]] static std::vector<nlohmann::json> ReadJsonFilesFromDirectory(
      const std::string &directory_path);

 private:
  /**
   * @brief Read a JSON file
   * @param file_path File path to read the JSON file from
   * @return A JSON object
   */
  [[nodiscard]] static nlohmann::json ReadJsonFile(const std::string &file_path);
};
}  // namespace rtype::server::game::utils
