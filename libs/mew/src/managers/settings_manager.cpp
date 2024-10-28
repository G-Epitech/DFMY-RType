/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings_manager.cpp
*/

#include "settings_manager.hpp"

using namespace mew::managers;

bool SettingsManager::Exists(const std::string &key) const {
  return settings_.find(key) != settings_.end();
}

void SettingsManager::Remove(const std::string &key) {
  settings_.erase(key);
}

void SettingsManager::Clear() {
  settings_.clear();
}
