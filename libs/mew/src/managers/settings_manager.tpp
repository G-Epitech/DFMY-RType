/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings_manager.cpp
*/

#pragma once

namespace mew::managers {
template <typename T>
T SettingsManager::Get(const std::string &key) const {
  return std::any_cast<T>(settings_.at(key));
}

template <typename T>
void SettingsManager::Set(const std::string &key, const T &value) {
  settings_[key] = value;
}

template <class T>
T &SettingsManager::operator[](const std::string &key) {
  return std::any_cast<T &>(settings_[key]);
}

template <class T>
const T &SettingsManager::operator[](const std::string &key) const {
  return std::any_cast<const T &>(settings_.at(key));
}
}  // namespace mew::managers
