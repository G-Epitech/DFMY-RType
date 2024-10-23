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
    : EventSystemBase<events::kMouseMoved, OnMouseMoved, drawable::Drawable>(
          std::move(window_manager)) {}

void MouseMoveEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                       sparse_array<OnMouseMoved>::ptr components,
                                       sparse_array<drawable::Drawable>::ptr drawables) {
  std::size_t entity_id = 0;

  for (auto& component : (*components)) {
    if (component) {
      HandleEventForEntity(entity_id, event, drawables, *component);
    }
    entity_id += 1;
  }
}

void MouseMoveEventSystem::HandleEventForEntity(
    std::size_t entityId, const sf::Event& event,
    const sparse_array<drawable::Drawable>::ptr& drawables,
    const std::optional<OnMouseMoved>& component) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y})
                         : sf::Vector2f{0, 0};
  if (!component || !window) {
    return;
  }
  auto current =
      MouseStrategyUtils::GetCurrentTarget<OnMouseMoved>(position, *component, drawables, entityId);
  if ((component->strategy == events::kAnyTarget) ||
      (current == events::kLocalTarget && component->strategy == events::kLocalTarget) ||
      (current == events::kOtherTarget && component->strategy == events::kOtherTarget)) {
    return component->handler(position, current);
  }
}
