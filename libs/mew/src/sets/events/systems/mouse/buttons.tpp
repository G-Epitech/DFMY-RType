/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.cpp
*/

#include "./strategy_utils.hpp"

namespace mew::sets::events {

template <EventType EventType, typename MouseEventComponent>
MouseButtonEventSystem<EventType, MouseEventComponent>::MouseButtonEventSystem(
    managers::WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, MouseEventComponent, drawable::Drawable>(
          std::move(window_manager)) {}

template <EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, sparse_array<MouseEventComponent>::ptr components,
    sparse_array<drawable::Drawable>::ptr drawables) {
  std::size_t entity_id = 0;

  for (auto& component : (*components)) {
    HandleEventForEntity(entity_id++, event, drawables, component);
  }
}

template <EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEventForEntity(
    const std::size_t entityId, const sf::Event& event,
    const sparse_array<drawable::Drawable>::ptr& drawables,
    const std::optional<MouseEventComponent>& component) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})
                         : sf::Vector2f{0, 0};
  if (!component || !window) {
    return;
  } else if (component->strategy == MouseEventTarget::kAnyTarget) {
    return component->handler(event.mouseButton.button, position, kAnyTarget);
  }

  auto target = MouseStrategyUtils::GetCurrentTarget<MouseEventComponent>(position, *component,
                                                                          drawables, entityId);
  auto v = component->strategy & target;
  switch (v) {
    case kLocalTarget:
    case kOtherTarget:
      return component->handler(event.mouseButton.button, position,
                                static_cast<MouseEventTarget>(target));
    default:
      return;
  }
}
}  // namespace mew::sets::events
