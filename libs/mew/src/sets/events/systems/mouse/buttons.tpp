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
    : EventSystemBase<EventType, MouseEventComponent>(std::move(window_manager)) {}

template <EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, zipper<MouseEventComponent> components) {
  const auto begin = components.begin();
  const auto end = components.end();
  const auto drawables = r->GetComponents<drawable::Drawable>();
  for (auto it = begin; it != end; ++it) {
    auto&& [entity_id, entity_components] = ~it;
    auto&& [on_mouse_button_event] = entity_components;
    HandleEventForEntity(entity_id, event, drawables, on_mouse_button_event);
  }
}

template <EventType EventType, typename MouseEventComponent>
void MouseButtonEventSystem<EventType, MouseEventComponent>::HandleEventForEntity(
    std::size_t entity_id, const sf::Event& event,
    const sparse_array<drawable::Drawable>::ptr& drawables, const MouseEventComponent& component) {
  auto window = this->windowManager_->window();
  auto position = window ? window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})
                         : sf::Vector2f{0, 0};
  if (!window) {
    return;
  }
  auto target = MouseStrategyUtils::GetCurrentTarget<MouseEventComponent>(position, component,
                                                                          drawables, entity_id);
  auto v = component.strategy & target;
  if (v == events::kNoTarget) {
    return;
  }
  return component.handler(event.mouseButton.button, position,
                           static_cast<MouseEventTarget>(target));
}
}  // namespace mew::sets::events
