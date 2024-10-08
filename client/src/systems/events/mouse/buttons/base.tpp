/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.cpp
*/

#include "components/on_event.hpp"

using namespace rtype::client::systems;

template <events::EventType EventType, typename MouseEventComponent>
MouseEventSystemBase<EventType, MouseEventComponent>::MouseEventSystemBase(
    WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, MouseEventComponent>(std::move(window_manager)) {}

template <events::EventType EventType, typename EventComponentType>
bool MouseEventSystemBase<EventType, EventComponentType>::IsStrategy(
    events::MouseEventStrategy strategy, events::MouseEventStrategy target) noexcept {
  return (strategy & target) == target;
}

template <events::EventType EventType, typename MouseEventComponent>
void MouseEventSystemBase<EventType, MouseEventComponent>::HandleLocalizedStrategy(
    const sf::Event& event, const MouseEventComponent& component,
    const sparse_array<components::Position>::ptr &positions, std::size_t entityId) {
  auto position =
      positions->size() > entityId ? (*positions)[entityId] : std::optional<components::Position>();
  if (!position) {
    std::cerr << "No position component found for entity " << entityId
              << " . Localized mouse strategy ignored." << std::endl;
    return;
  }

  // TODO: Check if the mouse is inside the entity
  bool is_inside = false;

  if (IsStrategy(component.strategy, events::MouseEventStrategy::kLocalTarget) && is_inside) {
    component.handler(event.mouseButton.button, {event.mouseButton.x, event.mouseButton.y});
  } else if (IsStrategy(component.strategy, events::MouseEventStrategy::kOtherTarget) &&
             !is_inside) {
    component.handler(event.mouseButton.button, {event.mouseButton.x, event.mouseButton.y});
  }
}

template <events::EventType EventType, typename MouseEventComponent>
void MouseEventSystemBase<EventType, MouseEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, sparse_array<MouseEventComponent>::ptr components) {
  auto length = components->size();
  auto positions = r->GetComponents<components::Position>();

  for (std::size_t i = 0; i < length; i++) {
    auto& component = (*components)[i];
    if (!component)
      continue;
    if (IsStrategy(component->strategy, events::MouseEventStrategy::kAnyTarget)) {
      component->handler(event.mouseButton.button, {event.mouseButton.x, event.mouseButton.y});
    } else {
      HandleLocalizedStrategy(event, *component, positions, i);
    }
  }
}
