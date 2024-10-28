/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** default.hpp
*/

#pragma once

#include "./resources_manager.hpp"
#include "./scenes_manager.hpp"
#include "./settings_manager.hpp"
#include "./sound_manager.hpp"
#include "./window_manager.hpp"

namespace mew::managers {
/// @brief Store the default managers of a Mew game
struct GameManagers {
  /**
   * @brief Store the window manager.
   */
  managers::WindowManager::Ptr window;

  /**
   * @brief Store the scenes manager.
   */
  managers::ScenesManager::Ptr scenes;

  /**
   * @brief Store the sound manager.
   */
  managers::SoundManager::Ptr sound;

  /**
   * @brief Store the resources manager.
   */
  managers::ResourcesManager::Ptr resources;

  /**
   * @brief Store the settings manager.
   */
  managers::SettingsManager::Ptr settings;
};
}  // namespace mew::managers
