/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "components/on_event.hpp"
#include "src/bases/systems/events_system_base.hpp"

namespace rtype::client::systems {
template <events::EventType EventType, typename KeyEventComponent>
class KeyEventSystemBase final : public EventSystemBase<EventType, KeyEventComponent> {
 public:
  explicit KeyEventSystemBase(WindowManager::Ptr window_manager);
  ~KeyEventSystemBase() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   zipper<typename sparse_array<KeyEventComponent>::ptr> components) final;
};

typedef KeyEventSystemBase<events::kKeyPressed, components::OnKeyPressed> KeyPressEventSystem;
typedef KeyEventSystemBase<events::kKeyReleased, components::OnKeyReleased> KeyReleaseEventSystem;

}  // namespace rtype::client::systems

#include "key.tpp"
