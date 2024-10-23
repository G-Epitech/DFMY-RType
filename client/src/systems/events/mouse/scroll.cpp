/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scroll.cpp
*/

#include "scroll.hpp"

#include <utility>

using namespace rtype::client::systems;

MouseScrollEventSystem::MouseScrollEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kMouseScrolled, components::OnMouseScrolled>(
          std::move(window_manager)) {}

void MouseScrollEventSystem::HandleEvent(
    const sf::Event& event, Registry::Ptr r,
    zipper<sparse_array<components::OnMouseScrolled>::ptr> components) {
  auto window = this->windowManager_->window();
  auto position =
      window ? window->mapPixelToCoords({event.mouseWheelScroll.x, event.mouseWheelScroll.y})
             : sf::Vector2f{0, 0};

  if (!window)
    return;
  for (auto&& [component] : components) {
    component.handler(position, event.mouseWheelScroll.delta);
  }
}
