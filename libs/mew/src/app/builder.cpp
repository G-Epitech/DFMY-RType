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

App::DefaultManagers AppBuilder::BuildDefaultManagers() {
  if (!windowProperties_)
    throw std::runtime_error("Window properties are required");
  WithService<managers::WindowManager>(*windowProperties_);
  WithService<managers::ScenesManager>();
  WithService<managers::SoundManager>();
  return {
      services_->Get<managers::WindowManager>(),
      services_->Get<managers::ScenesManager>(),
      services_->Get<managers::SoundManager>(),
  };
}
