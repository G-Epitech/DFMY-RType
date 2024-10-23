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
using namespace mew::app;

AppBuilder::AppBuilder() {
  services_ = DependenciesHandler::Create();
}

AppBuilder &AppBuilder::WithWindowProperties(
    const managers::WindowManager::Properties &properties) {
  windowProperties_ = properties;
  return *this;
}

App AppBuilder::Build() {
  return {services_, BuildDefaultManagers()};
}

DefaultManagers AppBuilder::BuildDefaultManagers() {
  if (!windowProperties_)
    throw std::runtime_error("Window properties are required");
  WithService<WindowManager>(*windowProperties_);
  WithService<ScenesManager>();
  WithService<SoundManager>();
  WithService<ResourcesManager>();
  return {
      services_->Get<WindowManager>(),
      services_->Get<ScenesManager>(),
      services_->Get<SoundManager>(),
      services_->Get<ResourcesManager>(),
  };
}
