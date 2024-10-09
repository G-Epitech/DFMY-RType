/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#pragma once

#include <iostream>
#include <utility>
using namespace rtype::client;

template <typename ContextType>
ScenesManager<ContextType>::ScenesManager(WindowManager::Ptr window_manager,
                                          const ContextType &context)
    : context_{context}, windowManager_{std::move(window_manager)} {}

template <typename ContextType>
void ScenesManager<ContextType>::SwitchToScene(IScene::Ptr new_scene) {
  if (currentScene_) {
    currentScene_->OnDeactivate();
  }
  currentScene_ = std::move(new_scene);
  if (currentScene_) {
    currentScene_->OnActivate();
  }
}

template <typename ContextType>
void ScenesManager<ContextType>::Update(utils::DeltaTime delta_time) {
  windowManager_->DeferEvents();
  if (currentScene_ && windowManager_->IsActive()) {
    currentScene_->Update(delta_time);
  }
  windowManager_->ClearEvents();
}

template <typename ContextType>
ScenesManager<ContextType>::Exception::Exception(std::string msg) : msg_{std::move(msg)} {}

template <typename ContextType>
const char *ScenesManager<ContextType>::Exception::what() const noexcept {
  return msg_.c_str();
}

template <typename ContextType>
template <SceneType T>
void ScenesManager<ContextType>::RegisterScene() {
  scenesMap_[std::type_index(typeid(T))] = nullptr;
}

template <typename ContextType>
template <SceneType T>
IScene::Ptr ScenesManager<ContextType>::CreateScene() {
  auto type = std::type_index(typeid(T));
  auto scene = scenesMap_[type] = std::make_shared<T>(context_);

  if (!scene)
    throw Exception("Failed to create scene: " + std::string(type.name()) + ".");
  scene->OnCreate();
  return scene;
}

template <typename ContextType>
template <SceneType T>
void ScenesManager<ContextType>::GoToScene() {
  IScene::Ptr scene = nullptr;
  const std::type_index scene_type = std::type_index(typeid(T));

  try {
    scene = scenesMap_.at(scene_type);
  } catch (const std::out_of_range &e) {
    throw Exception("Scene not registered: " + std::string(scene_type.name()) + ".");
  }

  if (!scene)
    scene = CreateScene<T>();
  SwitchToScene(scene);
}

template <typename ContextType>
void ScenesManager<ContextType>::Quit() {
  active_ = false;
}

template <typename ContextType>
bool ScenesManager<ContextType>::IsActive() const {
  return active_;
}
