/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "libs/mew/src/managers/scenes_manager.hpp"
#include "libs/mew/src/managers/sound_manager.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/porygon/src/handler.hpp"
#include "libs/zygarde/src/utils/timer/timer.hpp"

namespace mew::app {

class AppBuilder;

/**
 * @class App
 * @brief The main application class responsible for running the client-side application.
 *
 * This class provides the main entry point for the client application and contains
 * the necessary methods to initialize and Run the application.
 */

class App final {
  friend class AppBuilder;

 public:
  /**
   * @brief Default destructor for the App class.
   * Cleans up any resources used by the App class.
   */
  ~App() = default;

  /**
   * @brief Runs the client-side application.
   * This method contains the main loop and logic to start and maintain the client application.
   * @return int The exit code of the application.
   */
  int Run();

  /**
   * @brief Provides a read-only reference to the dependencies handler.
   * @return Dependencies handler.
   */
  const porygon::DependenciesHandler::Ptr &services;

  /**
   * @brief Store a read-only reference to the window manager.
   */
  const managers::WindowManager::Ptr &windowManager;

  /**
   * @brief Store a read-only reference to the scenes manager.
   */
  const managers::ScenesManager::Ptr &scenesManager;

  /**
   * @brief Store a read-only reference to the sound manager.
   */
  const managers::SoundManager::Ptr &soundManager;

 private:
  struct DefaultManagers {
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
  };

  /**
   * @brief Default constructor for the App class.
   * Initializes a new instance of the App class.
   * @param service The services provider to use for the application.
   * @param default_managers The default managers to use for the application.
   */
  App(porygon::DependenciesHandler::Ptr service, DefaultManagers default_managers);

  /**
   * @brief Store the services provider.
   */
  porygon::DependenciesHandler::Ptr services_;

  /**
   * @brief Store the default managers.
   */
  DefaultManagers defaultManagers_;

  /// @brief Timer
  zygarde::utils::Timer timer_;
};
}  // namespace mew::app
