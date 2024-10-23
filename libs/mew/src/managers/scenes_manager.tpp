/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#pragma once

#include <iostream>
#include <utility>

#include "libs/mew/src/utils/symbols.hpp"

namespace mew::managers {

template <scenes::SceneType T>
void ScenesManager::RegisterScene() {
  scenesMap_[std::type_index(typeid(T))] = nullptr;
}

template <scenes::SceneType T>
scenes::IScene::Ptr ScenesManager::CreateScene() {
  auto type = std::type_index(typeid(T));
  auto scene = scenesMap_[type] = std::make_shared<T>();

  if (!scene)
    throw Exception("Failed to Create scene: " + utils::GetTypeName<T>());
  scene->OnCreate();
  return scene;
}

template <scenes::SceneType T>
void ScenesManager::GoToScene() {
  scenes::IScene::Ptr scene = nullptr;
  const auto scene_type = std::type_index(typeid(T));

  try {
    scene = scenesMap_.at(scene_type);
  } catch (const std::out_of_range &_) {
    throw Exception("Scene not registered: " + utils::GetTypeName<T>());
  }

  if (!scene)
    scene = CreateScene<T>();
  SwitchToScene(scene);
}
}  // namespace mew::managers
