/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "./system_base.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/constants.hpp"

namespace mew::sets::events {
template <EventType EventType, typename KeyEventComponent>
class KeyEventSystemBase final : public EventSystemBase<EventType, KeyEventComponent> {
 public:
  explicit KeyEventSystemBase(managers::WindowManager::Ptr window_manager);
  ~KeyEventSystemBase() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   zipper<KeyEventComponent> components) final;
};

typedef KeyEventSystemBase<kKeyPressed, OnKeyPressed> KeyPressEventSystem;
typedef KeyEventSystemBase<kKeyReleased, OnKeyReleased> KeyReleaseEventSystem;

}  // namespace mew::sets::events

#include "./key.tpp"
