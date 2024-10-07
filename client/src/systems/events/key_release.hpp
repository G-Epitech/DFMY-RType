/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.hpp
*/

#pragma once

#include "system_base.hpp"
#include "window/window_manager.hpp"

namespace rtype::client::systems {
class KeyReleaseEventSystem final
    : public EventSystemBase<events::kKeyReleased, components::OnKeyReleased> {
 public:
  explicit KeyReleaseEventSystem(WindowManager::Ptr window_manager);
  ~KeyReleaseEventSystem() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   sparse_array<components::OnKeyReleased> &components) final;
};
}  // namespace rtype::client::systems
