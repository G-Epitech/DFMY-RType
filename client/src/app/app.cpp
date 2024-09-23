/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu]
** File description:
** app
*/

#include "app.hpp"

using namespace rtype;

App::App() {
    auto videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    mWindow.create(videoMode, APP_WINDOW_TITLE);
}

void App::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    sf::Event event;

    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }
}

void App::update() {}

void App::render() {
    mWindow.clear();
    mWindow.display();
}
