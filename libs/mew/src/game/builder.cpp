/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** factory.cpp
*/

#include "./builder.hpp"

#include "libs/mew/src/managers/scenes_manager.hpp"
#include "libs/mew/src/managers/sound_manager.hpp"
#include "libs/mew/src/managers/window_manager.hpp"

using namespace mew::managers;
using namespace mew::game;

GameBuilder::GameBuilder() {
  services_ = DependenciesHandler::Create();
}

GameBuilder &GameBuilder::WithWindowProperties(
    const managers::WindowManager::Properties &properties) {
  windowProperties_ = properties;
  return *this;
}

Game GameBuilder::Build() {
  return {services_, BuildDefaultManagers()};
}

GameManagers GameBuilder::BuildDefaultManagers() {
  if (!windowProperties_)
    throw std::runtime_error("Window properties are required");
  WithService<WindowManager>(*windowProperties_);
  WithService<ScenesManager>();
  WithService<SoundManager>();
  WithService<ResourcesManager>();
  WithService<SettingsManager>();
  return {
      .window = services_->Get<WindowManager>(),
      .scenes = services_->Get<ScenesManager>(),
      .sound = services_->Get<SoundManager>(),
      .resources = services_->Get<ResourcesManager>(),
      .settings = services_->Get<SettingsManager>(),
  };
}
