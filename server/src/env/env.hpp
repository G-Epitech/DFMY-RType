/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** config.hpp
*/

#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace rtype::server {
class Env {
  /// @brief Map of environment variables
  typedef std::unordered_map<std::string, std::any> EnvMap;

 public:
  /**
   * @brief Construct a new Env object
   * @param envPath The path to the environment file
   */
  explicit Env(const std::string& envPath);

  ~Env() = default;

  /**
   * @brief Get a value from the environment
   * @tparam T Type of the value to get
   * @param key Key of the value to get
   * @return The value
   */
  template <class T>
  T Get(const std::string& key);

 private:
  /**
   * @brief Load the environment from a file
   * @param envPath The path to the environment file
   */
  void Load(const std::string& envPath);

  /**
   * @brief Parse the environment file
   * @param file The file to parse
   */
  void ParseFile(std::ifstream& file);

  /**
   * @brief Parse a value from a string
   * @param envValue The string to parse
   * @return The parsed value with the correct type
   */
  static std::any ParseValueType(const std::string& envValue);

 private:
  /// @brief Map of environment variables
  EnvMap mEnv;
};
}  // namespace rtype::server

#include "env.tpp"
