/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "components/on_event.hpp"
#include "systems/events/base.hpp"

namespace rtype::client::systems {
template <events::EventType EventType, typename KeyEventComponent>
class KeyEventSystemBase final : public EventSystemBase<EventType, KeyEventComponent> {
 public:
  explicit KeyEventSystemBase(WindowManager::Ptr window_manager);
  ~KeyEventSystemBase() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   const sparse_array<KeyEventComponent> &components) final;
};
}  // namespace rtype::client::systems

#include "base.tpp"
