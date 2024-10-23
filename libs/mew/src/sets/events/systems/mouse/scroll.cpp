/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scroll.cpp
*/

#include "./scroll.hpp"

#include <utility>

using namespace mew::sets::events;
using namespace mew::managers;

MouseScrollEventSystem::MouseScrollEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kMouseScrolled, OnMouseScrolled>(std::move(window_manager)) {}

void MouseScrollEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                         sparse_array<OnMouseScrolled>::ptr components) {
  auto length = components->size();
  auto window = windowManager_->window();
  auto position =
      window ? window->mapPixelToCoords({event.mouseWheelScroll.x, event.mouseWheelScroll.y})
             : sf::Vector2f{0, 0};

  if (!window)
    return;
  for (std::size_t i = 0; i < length; i++) {
    auto component = (*components)[i];
    if (!component)
      continue;
    component->handler(position, event.mouseWheelScroll.delta);
  }
}
