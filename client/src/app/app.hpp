/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include <SFML/Graphics.hpp>

#define APP_WINDOW_WIDTH 800
#define APP_WINDOW_HEIGHT 600
#define APP_WINDOW_TITLE "R-Type"

#pragma once

namespace rtype {

    /**
     * @class App
     * @brief The main application class responsible for running the client-side application.
     *
     * This class provides the main entry point for the client application and contains
     * the necessary methods to initialize and run the application.
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
        void run();

    private:

        /**
         * @brief Processes events.
         */
        void processEvents();

        /**
         * @brief Updates the application.
         */
        void update();

        /**
         * @brief Renders the application.
         */
        void render();

        /// @brief The main window for the application.
        sf::RenderWindow mWindow;

        /// @brief Vector example.
        std::vector<sf::RectangleShape> mRectangles;
    };
}
