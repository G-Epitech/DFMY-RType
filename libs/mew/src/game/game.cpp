/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game
*/

#include "./game.hpp"

#include <utility>

#include "managers/scenes_manager.hpp"

using namespace mew::game;
using namespace mew::managers;

Game::Game(DependenciesHandler::Ptr service, GameManagers default_managers)
    : services_(std::move(service)),
      services{services_},
      managers_{std::move(default_managers)},
      managers{managers_} {
  timer_.Initialize();
}

int Game::Run() {
  try {
    while (managers_.scenes->IsActive()) {
      timer_.Update();
      managers_.scenes->Update(timer_.GetDeltaTime());
    }
  } catch (const std::exception &e) {
    std::cerr << "Mew game terminated: " << e.what() << std::endl;
    return 84;
  }
  return 0;
}
