/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.cpp
*/

#include "scenes_manager.hpp"

#include <iostream>
#include <utility>

using namespace rtype::client;

ScenesManager::ScenesManager(const GlobalContext& context) : context_{context} {}

void ScenesManager::SwitchToScene(IScene::Ptr new_scene) {
  if (currentScene_) {
    currentScene_->OnDeactivate();
  }
  currentScene_ = std::move(new_scene);
  if (currentScene_) {
    currentScene_->OnActivate();
  }
}

void ScenesManager::Update(utils::DeltaTime delta_time) {
  if (currentScene_) {
    currentScene_->Update(delta_time);
  } else {
    std::cerr << "[WARN]: No scene to update" << std::endl;
  }
}

void ScenesManager::Draw() {
  if (currentScene_) {
    currentScene_->Draw();
  } else {
    std::cerr << "[WARN]: No scene to draw" << std::endl;
  }
}

ScenesManager::Exception::Exception(std::string msg) : msg_{std::move(msg)} {}

const char* ScenesManager::Exception::what() const noexcept {
  return msg_.c_str();
}
