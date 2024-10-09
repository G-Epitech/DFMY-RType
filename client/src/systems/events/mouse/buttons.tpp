/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.cpp
*/

#include "components/on_event.hpp"
#include "strategy_utils.hpp"

using namespace rtype::client::systems;

template <events::EventType EventType, typename MouseEventComponent>
MouseButtonEventSystem<EventType, MouseEventComponent>::MouseButtonEventSystem(
    WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, MouseEventComponent, components::Drawable>(
          std::move(window_manager)) {}

template <events::EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, sparse_array<MouseEventComponent>::ptr components,
    sparse_array<components::Drawable>::ptr drawables) {
  std::size_t entity_id = 0;

  for (auto& component : (*components)) {
    HandleEventForEntity(entity_id++, event, drawables, component);
  }
}

template <events::EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEventForEntity(
    const std::size_t entityId, const sf::Event& event,
    const sparse_array<components::Drawable>::ptr& drawables,
    const std::optional<MouseEventComponent>& component) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})
                         : sf::Vector2f{0, 0};
  if (!component || !window) {
    return;
  } else if (component->strategy == events::MouseEventTarget::kAnyTarget) {
    return component->handler(event.mouseButton.button, position, events::kAnyTarget);
  }

  auto target = MouseStrategyUtils::GetCurrentTarget<MouseEventComponent>(position, *component,
                                                                          drawables, entityId);
  auto v = component->strategy & target;
  switch (v) {
    case events::kLocalTarget:
    case events::kOtherTarget:
      return component->handler(event.mouseButton.button, position,
                                static_cast<events::MouseEventTarget>(target));
    default:
      return;
  }
}
