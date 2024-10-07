/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.cpp
*/

#include "key_release.hpp"

using namespace rtype::client::systems;

KeyReleaseEventSystem::KeyReleaseEventSystem(WindowManager::Ptr window_manager)
    : EventSystemBase<events::kKeyReleased, components::OnKeyReleased>(std::move(window_manager)) {}

void KeyReleaseEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                      sparse_array<components::OnKeyReleased>& components) {
  for (auto& component : components) {
    if (component)
      component->handler(event.key.code);
  }
}
