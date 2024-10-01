/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "app.hpp"

#include "my_scene.hpp"
#include "scenes/scenes_manager.hpp"

using namespace rtype::client;

App::App() {
  const auto videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);

  window_ = std::make_shared<sf::RenderWindow>(videoMode, APP_WINDOW_TITLE);
  window_->setFramerateLimit(60);

  scenesManager_ = std::make_shared<ScenesManager>(globalContext_);

  globalContext_ = {
      .window = window_,
      .scenesManager = scenesManager_,
  };

  scenesManager_->RegisterScene<MyScene>();
}

void App::Run() {
  scenesManager_->GoToScene<MyScene>();
  while (window_->isOpen()) {
    processEvents();
    update();
    render();
  }
}

void App::processEvents() {
  sf::Event event{};

  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    }
  }
}

void App::update() {}

void App::render() {
  window_->clear();

  window_->display();
}
