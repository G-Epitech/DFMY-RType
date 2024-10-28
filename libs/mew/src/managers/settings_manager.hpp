/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings_manager.hpp
*/

#pragma once

#include <any>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>

namespace mew::managers {
class SettingsManager {
 public:
  /// @brief Shared pointer to a SettingsManager
  using Ptr = std::shared_ptr<SettingsManager>;

  /**
   * @brief Construct a new Settings Manager object
   */
  SettingsManager() = default;

  /**
   * @brief Destroy the Settings Manager object
   */
  ~SettingsManager() = default;

  /**
   * @brief Set a setting
   * @tparam T Setting type
   * @param key Setting key
   * @param value Setting value
   */
  template <typename T>
  void Set(const std::string& key, const T& value);

  /**
   * @brief Get a setting
   * @tparam T Setting type
   * @param key Setting key
   * @return Setting value
   * @throw std::bad_any_cast if the setting is not of the requested type
   * @throw std::out_of_range if the setting does not exist
   */
  template <typename T>
  T Get(const std::string& key) const;

  /**
   * @brief Check if a setting exists
   * @param key Setting key
   * @return true if the setting exists, false otherwise
   */
  [[nodiscard]] bool Exists(const std::string& key) const;

  /**
   * @brief Remove a setting
   * @param key Setting key
   */
  void Remove(const std::string& key);

  /**
   * @brief Clear all settings
   */
  void Clear();

  /**
   * @brief Get reference to a setting
   * @tparam T Type of the setting
   * @param key Key of the setting
   * @return Reference to the setting
   * @throw std::out_of_range if the setting does not exist
   * @throw std::bad_any_cast if the setting is not of the requested type
   */
  template <class T>
  T& operator[](const std::string& key);

  /**
   * @brief Get const reference to a setting
   * @tparam T Type of the setting
   * @param key Key of the setting
   * @return Const reference to the setting
   * @throw std::out_of_range if the setting does not exist
   * @throw std::bad_any_cast if the setting is not of the requested type
   */
  template <class T>
  const T& operator[](const std::string& key) const;

 private:
  // @brief Settings map
  std::map<std::string, std::any> settings_;
};
}  // namespace mew::managers

#include "./settings_manager.tpp"
