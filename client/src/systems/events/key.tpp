/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.tpp
*/

#pragma once

using namespace rtype::client::systems;

template <events::EventType EventType, typename KeyEventComponent>
KeyEventSystemBase<EventType, KeyEventComponent>::KeyEventSystemBase(
    WindowManager::Ptr window_manager)
    : EventSystemBase<EventType, KeyEventComponent>(window_manager) {}

template <events::EventType EventType, typename KeyEventComponent>
void KeyEventSystemBase<EventType, KeyEventComponent>::HandleEvent(
    const sf::Event& event, Registry::Ptr r,
    zipper<typename sparse_array<KeyEventComponent>::ptr> components) {
  for (auto&& [component] : components) {
    component.handler(event.key.code);
  }
}
