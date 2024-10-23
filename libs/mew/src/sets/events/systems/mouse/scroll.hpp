/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scroll.hpp
*/

#pragma once

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/systems/system_base.hpp"

namespace mew::sets::events {
class MouseScrollEventSystem : public EventSystemBase<events::kMouseScrolled, OnMouseScrolled> {
 public:
  /**
   * @brief Construct a new Mouse Scroll Event System object
   * @param window_manager Window manager to use
   */
  explicit MouseScrollEventSystem(managers::WindowManager::Ptr window_manager);

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   sparse_array<OnMouseScrolled>::ptr components) override;
};
}  // namespace mew::sets::events
