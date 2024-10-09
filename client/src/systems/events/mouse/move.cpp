/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Move.cpp
*/

#include "move.hpp"

#include <utility>

#include "strategy_utils.hpp"

using namespace rtype::client::systems;

MouseMoveEventSystem::MouseMoveEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kMouseMoved, components::OnMouseMoved, components::Drawable>(
          std::move(window_manager)) {}

void MouseMoveEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                       sparse_array<components::OnMouseMoved>::ptr components,
                                       sparse_array<components::Drawable>::ptr drawables) {
  std::size_t entity_id = 0;

  for (auto& component : (*components)) {
    HandleEventForEntity(entity_id++, event, drawables, *component);
  }
}

void MouseMoveEventSystem::HandleEventForEntity(
    std::size_t entityId, const sf::Event& event,
    const sparse_array<components::Drawable>::ptr& drawables,
    const std::optional<components::OnMouseMoved>& component) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y})
                         : sf::Vector2f{0, 0};
  if (!component || !window) {
    return;
  }
  auto current = MouseStrategyUtils::GetCurrentTarget<components::OnMouseMoved>(
      position, *component, drawables, entityId);
  if ((component->strategy == events::kAnyTarget) ||
      (current == events::kLocalTarget && component->strategy == events::kLocalTarget) ||
      (current == events::kOtherTarget && component->strategy == events::kOtherTarget)) {
    return component->handler(position, current);
  }
}
