/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.cpp
*/

#include "key_press.hpp"

using namespace rtype::client::systems;

KeyPressEventSystem::KeyPressEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kKeyPressed, components::OnKeyPressed>(std::move(window_manager)) {}

void KeyPressEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                      sparse_array<components::OnKeyPressed>& components) {
  for (auto& component : components) {
    if (component)
      component->handler(event.key.code);
  }
}
