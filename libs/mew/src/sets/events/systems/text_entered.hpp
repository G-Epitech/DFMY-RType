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
class EXPORT_MEW_API TextEnteredEventSystem final
    : public EventSystemBase<kTextEntered, OnTextEntered> {
 public:
  explicit TextEnteredEventSystem(managers::WindowManager::Ptr window_manager);
  ~TextEnteredEventSystem() final;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r, zipper<OnTextEntered> components) final;
};

}  // namespace mew::sets::events
