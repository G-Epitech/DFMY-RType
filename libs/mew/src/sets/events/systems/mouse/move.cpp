/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Move.cpp
*/

#include "./move.hpp"

#include <utility>

#include "./strategy_utils.hpp"

using namespace mew::sets::events;
using namespace mew::managers;

MouseMoveEventSystem::MouseMoveEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kMouseMoved, OnMouseMoved>(std::move(window_manager)) {}

void MouseMoveEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                       zipper<OnMouseMoved> components) {
  const auto begin = components.begin();
  const auto end = components.end();
  const auto drawables = r->GetComponents<drawable::Drawable>();
  for (auto it = begin; it != end; ++it) {
    auto&& [entity_index, entity_components] = ~it;
    auto&& [on_mouse_moved] = entity_components;
    HandleEventForEntity(entity_index, event, drawables, on_mouse_moved);
  }
}

void MouseMoveEventSystem::HandleEventForEntity(
    std::size_t entity_id, const sf::Event& event,
    const sparse_array<drawable::Drawable>::ptr& drawables, const OnMouseMoved& on_mouse_moved) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y})
                         : sf::Vector2f{0, 0};
  if (!window) {
    return;
  }
  auto current = MouseStrategyUtils::GetCurrentTarget<OnMouseMoved>(position, on_mouse_moved,
                                                                    drawables, entity_id);
  if ((on_mouse_moved.strategy == events::kAnyTarget) ||
      (current == events::kLocalTarget && on_mouse_moved.strategy == events::kLocalTarget) ||
      (current == events::kOtherTarget && on_mouse_moved.strategy == events::kOtherTarget)) {
    return on_mouse_moved.handler(position, current);
  }
}
