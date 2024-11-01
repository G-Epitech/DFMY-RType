/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** text.tpp
*/

#pragma once

namespace mew::sets::events {

template <EventType EventType, typename KeyEventComponent>
TextEventSystemBase<EventType, KeyEventComponent>::TextEventSystemBase(
    managers::WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, KeyEventComponent>(window_manager) {}

template <EventType EventType, typename KeyEventComponent>
void TextEventSystemBase<EventType, KeyEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r, zipper<KeyEventComponent> components) {
  for (auto&& [keyEvent] : components) {
    keyEvent.handler(event.text.unicode);
  }
}
}  // namespace mew::sets::events
