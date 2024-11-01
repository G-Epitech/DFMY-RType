/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** text.hpp
*/

#pragma once

#include "./system_base.hpp"
#include "libs/mew/include/api.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/constants.hpp"

namespace mew::sets::events {
template <EventType EventType, typename KeyEventComponent>
class EXPORT_MEW_API TextEventSystemBase final
    : public EventSystemBase<EventType, KeyEventComponent> {
 public:
  explicit TextEventSystemBase(managers::WindowManager::Ptr window_manager);
  ~TextEventSystemBase() final = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   zipper<KeyEventComponent> components) final;
};

typedef TextEventSystemBase<kTextEntered, OnTextEntered> TextEnteredEventSystem;

}  // namespace mew::sets::events

#include "./text.tpp"
