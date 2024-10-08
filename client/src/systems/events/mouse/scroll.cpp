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
    sparse_array<components::OnMouseScrolled>::ptr components) {
  auto length = components->size();

  for (std::size_t i = 0; i < length; i++) {
    auto component = (*components)[i];
    if (!component)
      continue;
    component->handler(
        {
            event.mouseWheelScroll.x,
            event.mouseWheelScroll.y,
        },
        event.mouseWheelScroll.delta);
  }
}
