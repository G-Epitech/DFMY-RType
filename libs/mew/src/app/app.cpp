/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app
*/

#include "./app.hpp"

#include <utility>

#include "managers/scenes_manager.hpp"

using namespace mew::app;
using namespace mew::managers;

App::App(DependenciesHandler::Ptr service, DefaultManagers default_managers)
    : services_(std::move(service)),
      services{services_},
      defaultManagers_{std::move(default_managers)},
      windowManager{defaultManagers_.window},
      scenesManager{defaultManagers_.scenes},
      soundManager{defaultManagers_.sound} {
  timer_.Initialize();
}

int App::Run() {
  try {
    while (scenesManager->IsActive()) {
      timer_.Update();
      scenesManager->Update(timer_.GetDeltaTime());
    }
  } catch (const std::exception &e) {
    std::cerr << "Mew app terminated: " << e.what() << std::endl;
    return 84;
  }
  return 0;
}
