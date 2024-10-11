/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "app.hpp"

#include "scenes/menu.hpp"

using namespace rtype::client;

App::App() {
  CreateWindowManager();
  CreateScenesManager();
  InitializeGlobalContext();

  scenesManager_->RegisterScene<SceneMenu>();
  scenesManager_->GoToScene<SceneMenu>();
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
  windowManager_ =
      WindowManager::Create({.title = APP_WINDOW_TITLE,
                             .videoMode = sf::VideoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT),
                             .style = sf::Style::Default,
                             .contextSettings = sf::ContextSettings(),
                             .frameLimit = APP_WINDOW_FRAMERATE,
                             .iconPath = APP_WINDOW_ICON_PATH});
}

void App::CreateScenesManager() {
  scenesManager_ = ScenesManager<GlobalContext>::Create(windowManager_, globalContext_);
}
