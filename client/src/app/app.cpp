/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "app.hpp"

#include "my_scene.hpp"
#include "my_scene_2.hpp"
#include "scenes/scenes_manager.hpp"

using namespace rtype::client;

App::App() {
  CreateWindow();
  CreateScenesManager();
  InitializeGlobalContext();

  scenesManager_->RegisterScene<MyScene>();
  scenesManager_->RegisterScene<MyScene2>();
  scenesManager_->GoToScene<MyScene>();
}

void App::Run() {
  while (window_->isOpen()) {
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
  window_->setFramerateLimit(60);
}

void App::CreateScenesManager() {
  scenesManager_ = std::make_shared<ScenesManager<GlobalContext>>(globalContext_);
}
