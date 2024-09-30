/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** config.hpp
*/

#pragma once

#include <any>
#include <string>
#include <map>

namespace rtype::server {
class Config {
  /// @brief Map of config variables
  typedef std::map<std::string, std::any> ConfigMap;

 public:
  /**
   * @brief Construct a new Config object
   * @param configPath The path to the config file
   */
  explicit Config(const std::string& configPath);

  ~Config() = default;

  /**
   * @brief Get a value from the config
   * @tparam T Type of the value to get
   * @param key Key of the value to get
   * @return The value
   */
  template <class T>
  T Get(const std::string& key);

 private:
  /**
   * @brief Load the config from a file
   * @param configPath The path to the config file
   */
  void Load(const std::string& configPath);

  /**
   * @brief Parse the config file
   * @param file The file to parse
   */
  void ParseFile(std::ifstream& file);

  /**
   * @brief Parse a value from a string
   * @param configValue The string to parse
   * @return The parsed value with the correct type
   */
  static std::any ParseValueType(const std::string& configValue);

 private:
  /// @brief Map of config variables
  ConfigMap configMap_;
};
}  // namespace rtype::server

#include "config.tpp"
