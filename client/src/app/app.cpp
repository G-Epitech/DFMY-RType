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
  CreateWindowManager();
  CreateScenesManager();
  InitializeGlobalContext();

  scenesManager_->RegisterScene<MyScene>();
  scenesManager_->RegisterScene<MyScene2>();
  scenesManager_->GoToScene<MyScene>();
}

void App::Run() {
  while (scenesManager_->IsActive() && windowManager_->IsActive()) {
    scenesManager_->Update(++timer_);
  }
}

void App::InitializeGlobalContext() {
  globalContext_.windowManager = windowManager_;
  globalContext_.scenesManager = scenesManager_;
}

void App::CreateWindowManager() {
  windowManager_ = WindowManager::Create({
      .title = APP_WINDOW_TITLE,
      .videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT),
      .style = sf::Style::Default,
      .contextSettings = sf::ContextSettings()
  });
}

void App::CreateScenesManager() {
  scenesManager_ = ScenesManager<GlobalContext>::Create(windowManager_, globalContext_);
}
