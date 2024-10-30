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

  [[nodiscard]] static std::vector<nlohmann::json> ReadJsonFilesFromDirectory(
      const std::string &directory_path);

 private:
  [[nodiscard]] static nlohmann::json ReadJsonFile(const std::string &file_path);
};
}  // namespace rtype::server::game::utils
