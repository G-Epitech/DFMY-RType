/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.tpp
*/

#pragma once

namespace mew::sets::events {

template <EventType EventType, typename KeyEventComponent>
KeyEventSystemBase<EventType, KeyEventComponent>::KeyEventSystemBase(
    managers::WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, KeyEventComponent>(window_manager) {}

template <EventType EventType, typename KeyEventComponent>
void KeyEventSystemBase<EventType, KeyEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, sparse_array<KeyEventComponent>::ptr components) {
  for (auto& component : (*components)) {
    if (component)
      component->handler(event.key.code);
  }
}
}  // namespace mew::sets::events
