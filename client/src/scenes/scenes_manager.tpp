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
IScene::Ptr ScenesManager::CreateScene() {
  auto type = std::type_index(typeid(T));
  auto scene = scenesMap_[type] = std::make_shared<T>(context_);

  if (!scene)
    throw Exception("Failed to create scene: " + std::string(type.name()) + ".");
  scene->OnCreate();
  return scene;
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
    scene = CreateScene<T>();
  SwitchToScene(scene);
}
