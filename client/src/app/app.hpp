/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include <SFML/Graphics.hpp>

#include "context/global_context.hpp"
#include "scenes/scenes_manager.hpp"
#include "utils/timer.hpp"

#define APP_WINDOW_WIDTH 800
#define APP_WINDOW_HEIGHT 600
#define APP_WINDOW_TITLE "R-Type"
#define APP_WINDOW_FRAMERATE 60

#pragma once

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
  void CreateWindow();

  /**
   * @brief Creates the scenes manager for the application.
   */
  void CreateScenesManager();

  /**
   * @brief Processes events.
   */
  void ProcessEvents();

  /**
   * @brief Updates the application.
   */
  void Update(utils::DeltaTime delta_time);

  /**
   * @brief Renders the application.
   */
  void Render();

  /// @brief The main window for the application.
  std::shared_ptr<sf::RenderWindow> window_;

  /// @brief The scenes manager for the application.
  ScenesManager<GlobalContext>::Ptr scenesManager_;

  /// @brief The global context for the application.
  GlobalContext globalContext_;

  /// @brief App timer
  utils::Timer timer_;
};
}  // namespace rtype::client
