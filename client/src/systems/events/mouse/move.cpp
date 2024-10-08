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
    : EventSystemBase<events::kMouseMoved, components::OnMouseMoved>(std::move(window_manager)) {}

void MouseMoveEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                       sparse_array<components::OnMouseMoved>::ptr components) {
  std::size_t entity_id = 0;

  for (auto& component : (*components)) {
  }
}

void MouseMoveEventSystem::HandleEventForEntity(
    std::size_t entityId, const sf::Event& event,
    const sparse_array<components::Drawable>::ptr & drawables,
    const std::optional<components::OnMouseMoved>& component) {
  if (!component) {
    return;
  }
  auto target =
      component->strategy & MouseStrategyUtils::GetCurrentTarget<components::OnMouseMoved>(
                                event.mouseButton, *component, drawables, entityId);
  switch (target) {
    case events::kLocalTarget:
    case events::kOtherTarget:
      return component->handler({event.mouseButton.x, event.mouseButton.y},
                                static_cast<events::MouseEventTarget>(event.type));
    default:
      return;
  }
}
