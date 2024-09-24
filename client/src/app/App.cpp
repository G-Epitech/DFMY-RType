/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "App.hpp"

using namespace rtype;

App::App() {
  auto videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);

  mWindow.create(videoMode, APP_WINDOW_TITLE);
  mWindow.setFramerateLimit(60);

  // The following code snippet is used to create a vector of rectangles.
  // This is just a simple example in order to test the rendering of multiple objects.
  sf::RectangleShape rectangle(sf::Vector2f(100, 100));
  rectangle.setFillColor(sf::Color::Red);
  for (int i = 0; i < 10; i++) {
    rectangle.setPosition(i * 100, i * 100);
    mRectangles.push_back(rectangle);
  }
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

  // The following code snippet is used to render the vector of rectangles.
  // It is just a simple example and have to be removed.
  for (auto &rectangle : mRectangles) {
    mWindow.draw(rectangle);
  }

  mWindow.display();
}
