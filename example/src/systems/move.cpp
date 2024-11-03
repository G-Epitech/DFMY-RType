/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** move.cpp
*/

#include "move.hpp"

MoveSystem::MoveSystem(mew::managers::WindowManager::Ptr window_manager)
    : windowManager_{std::move(window_manager)} {}

void MoveSystem::Run(Registry::Ptr r, ZippedComponents components) {
  const auto events = windowManager_->GetDeferredEvents();

  for (auto&& [tags, rigidbody] : components) {
    if (tags & "player") {
      for (auto event : events) {
        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Z) {
            rigidbody.SetVelocity({0, -200});
          }
          if (event.key.code == sf::Keyboard::S) {
            rigidbody.SetVelocity({0, 200});
          }
          if (event.key.code == sf::Keyboard::Q) {
            rigidbody.SetVelocity({-200, 0});
          }
          if (event.key.code == sf::Keyboard::D) {
            rigidbody.SetVelocity({200, 0});
          }
        }
      }
    }
  }
}
