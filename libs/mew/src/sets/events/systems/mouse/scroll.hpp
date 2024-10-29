/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scroll.hpp
*/

#pragma once

#include "libs/mew/include/api.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/systems/system_base.hpp"

namespace mew::sets::events {
class EXPORT_MEW_API MouseScrollEventSystem final
    : public EventSystemBase<events::kMouseScrolled, OnMouseScrolled> {
 public:
  /**
   * @brief Construct a new Mouse Scroll Event System object
   * @param window_manager Window manager to use
   */
  explicit MouseScrollEventSystem(managers::WindowManager::Ptr window_manager);

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   zipper<OnMouseScrolled> components) final;
};
}  // namespace mew::sets::events
