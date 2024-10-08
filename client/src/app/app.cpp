/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "app.hpp"

#include "./scenes/menu.hpp"
#include "scenes/scenes_manager.hpp"

using namespace rtype::client;

App::App() {
  CreateWindow();
  CreateScenesManager();
  InitializeGlobalContext();

  scenesManager_->RegisterScene<SceneMenu>();
  scenesManager_->GoToScene<SceneMenu>();
}

void App::Run() {
  while (window_->isOpen() && scenesManager_->IsActive()) {
    timer_.tick();
    ProcessEvents();
    Update(timer_.GetElapsedTime());
    Render();
  }
}

void App::ProcessEvents() {
  sf::Event event{};

  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    }
  }
}

void App::Update(utils::DeltaTime delta_time) {
  scenesManager_->Update(delta_time);
}

void App::Render() {
  window_->clear();
  scenesManager_->Draw();
  window_->display();
}

void App::InitializeGlobalContext() {
  globalContext_.window = window_;
  globalContext_.scenesManager = scenesManager_;
}

void App::CreateWindow() {
  const auto videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);

  window_ = std::make_shared<sf::RenderWindow>(videoMode, APP_WINDOW_TITLE);
  window_->setFramerateLimit(APP_WINDOW_FRAMERATE);
  if (logo_.loadFromFile(APP_WINDOW_ICON_PATH)) {
    window_->setIcon(logo_.getSize().x, logo_.getSize().y, logo_.getPixelsPtr());
  }
}

void App::CreateScenesManager() {
  scenesManager_ = std::make_shared<ScenesManager<GlobalContext>>(globalContext_);
}
