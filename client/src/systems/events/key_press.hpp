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
class KeyPressEventSystem final
    : public EventSystemBase<events::kKeyPressed, components::OnKeyPressed> {
 public:
  explicit KeyPressEventSystem(WindowManager::Ptr window_manager);
  ~KeyPressEventSystem() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   sparse_array<components::OnKeyPressed> &components) final;
};
}  // namespace rtype::client::systems
