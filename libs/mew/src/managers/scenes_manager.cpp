/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#include "managers/scenes_manager.hpp"

#include <iostream>
#include <utility>

#include "utils/symbols.hpp"

using namespace mew::managers;
using namespace mew::scenes;

ScenesManager::ScenesManager(DependenciesHandler::Ptr services)
    : ManagerBase(std::move(services)), scenesMap_{} {
  windowManager_ = services_->Get<WindowManager>();
}

void ScenesManager::SwitchToScene(IScene::Ptr new_scene) {
  if (currentScene_) {
    currentScene_->OnDeactivate();
  }
  currentScene_ = std::move(new_scene);
  if (currentScene_) {
    currentScene_->OnActivate();
  }
}

void ScenesManager::Update(zygarde::utils::Timer::Nanoseconds delta_time) {
  windowManager_->DeferEvents();
  if (currentScene_ && windowManager_->IsActive()) {
    currentScene_->Update(delta_time);
  } else if (!windowManager_->IsActive()) {
    Quit();
  }
  windowManager_->ClearEvents();
}

ScenesManager::Exception::Exception(std::string msg) : msg_{std::move(msg)} {}

const char *ScenesManager::Exception::what() const noexcept {
  return msg_.c_str();
}

void ScenesManager::Quit() {
  active_ = false;
}

bool ScenesManager::IsActive() const {
  return active_;
}
