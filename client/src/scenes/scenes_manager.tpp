/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#pragma once

using namespace rtype::client;

template <SceneType T>
void ScenesManager::RegisterScene() {
  scenesMap_[std::type_index(typeid(T))] = nullptr;
}

template <SceneType T>
void ScenesManager::GoToScene() {
  IScene::Ptr scene = nullptr;
  const std::type_index scene_type = std::type_index(typeid(T));

  try {
    scene = scenesMap_.at(scene_type);
  } catch (const std::out_of_range &e) {
    throw Exception("Scene not registered: " + std::string(scene_type.name()) + ".");
  }
  if (!scene)
    scene = scenesMap_[scene_type] = std::make_shared<T>();
  if (!scene)
    throw Exception("Failed to go to scene: " + std::string(scene_type.name()) + ".");
  scene->Draw();
}
