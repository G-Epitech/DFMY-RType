/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "context/global.hpp"
#include "libs/game/includes/api.hpp"
#include "managers/scenes_manager.hpp"
#include "utils/timer.hpp"

#define APP_WINDOW_WIDTH 1920
#define APP_WINDOW_HEIGHT 1080
#define APP_WINDOW_TITLE "R-Type"
#define APP_WINDOW_FRAMERATE 60
#define APP_WINDOW_ICON_PATH "assets/icons/R-Type.png"

#define APP_IP "127.0.0.1"
#define APP_PORT 5001

namespace rtype::client {

/**
 * @class App
 * @brief The main application class responsible for running the client-side application.
 *
 * This class provides the main entry point for the client application and contains
 * the necessary methods to initialize and Run the application.
 */
class App {
 public:
  /**
   * @brief Default constructor for the App class.
   * Initializes a new instance of the App class.
   */
  App();

  /**
   * @brief Default destructor for the App class.
   * Cleans up any resources used by the App class.
   */
  ~App() = default;

  /**
   * @brief Runs the client-side application.
   * This method contains the main loop and logic to start and maintain the client application.
   */
  void Run();

 private:
  /**
   * @brief Initializes the global context for the application.
   */
  void InitializeGlobalContext();

  /**
   * @brief Creates the main window for the application.
   */
  void CreateWindowManager();

  /**
   * @brief Creates the scenes manager for the application.
   */
  void CreateScenesManager();

  /**
   * @brief Creates the sound manager for the application.
   */
  void CreateSoundManager();

  /**
   * @brief Creates the client API for the application.
   */
  void CreateClient();

  /// @brief The main window for the application.
  WindowManager::Ptr windowManager_;

  /// @brief The scenes manager for the application.
  ScenesManager<GlobalContext>::Ptr scenesManager_;

  /// @brief The sound manager for the application.
  SoundManager::Ptr soundManager_;

  /// @brief The client API for the application.
  std::shared_ptr<rtype::sdk::game::api::Client> client_;

  /// @brief The global context for the application.
  GlobalContext globalContext_;

  /// @brief App timer
  utils::Timer timer_;

  /// @brief App logo
  sf::Image logo_;
};
}  // namespace rtype::client
