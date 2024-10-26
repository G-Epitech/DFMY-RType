/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scroll.hpp
*/

#pragma once

#include "src/bases/systems/events_system_base.hpp"

namespace rtype::client::systems {
class MouseScrollEventSystem
    : public EventSystemBase<events::kMouseScrolled, components::OnMouseScrolled> {
 public:
  /**
   * @brief Construct a new Mouse Scroll Event System object
   * @param window_manager Window manager to use
   */
  explicit MouseScrollEventSystem(WindowManager::Ptr window_manager);

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   sparse_array<components::OnMouseScrolled>::ptr components) override;
};
}  // namespace rtype::client::systems
