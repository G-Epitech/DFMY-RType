/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "libs/mew/src/managers/managers.hpp"
#include "libs/porygon/src/handler.hpp"
#include "libs/zygarde/src/utils/timer/timer.hpp"

namespace mew::game {

class GameBuilder;

/**
 * @class App
 * @brief The main application class responsible for running the client-side application.
 *
 * This class provides the main entry point for the client application and contains
 * the necessary methods to initialize and Run the application.
 */

class Game final {
  friend class GameBuilder;

 public:
  /**
   * @brief Default destructor for the App class.
   * Cleans up any resources used by the App class.
   */
  ~Game() = default;

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
  const managers::GameManagers &managers;

 private:
  /**
   * @brief Default constructor for the Game class.
   * Initializes a new instance of the Game.
   * @param service The services provider to use for the application.
   * @param default_managers The default managers to use for the application.
   */
  Game(porygon::DependenciesHandler::Ptr service, managers::GameManagers default_managers);

  /**
   * @brief Store the services provider.
   */
  porygon::DependenciesHandler::Ptr services_;

  /**
   * @brief Store the default managers.
   */
  managers::GameManagers managers_;

  /// @brief Timer
  zygarde::utils::Timer timer_;
};
}  // namespace mew::game
