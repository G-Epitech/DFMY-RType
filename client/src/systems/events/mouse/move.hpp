/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** move.hpp
*/

#pragma once

#include "components/drawable.hpp"
#include "systems/events/base.hpp"

namespace rtype::client::systems {
class MouseMoveEventSystem
    : public EventSystemBase<events::kMouseMoved, components::OnMouseMoved, components::Drawable> {
 public:
  /**
   * @brief Construct a new Mouse Move Event System object
   * @param window_manager Window manager to use
   */
  explicit MouseMoveEventSystem(WindowManager::Ptr window_manager);

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   sparse_array<components::OnMouseMoved>::ptr components,
                   sparse_array<components::Drawable>::ptr drawables) override;
  /**
   * @brief Handle the event for the entity
   * @param entityId Entity id
   * @param event Event to handle
   * @param drawables Drawables components
   * @param component Component to handle
   */
  void HandleEventForEntity(std::size_t entityId, const sf::Event& event,
                            const sparse_array<components::Drawable>::ptr& drawables,
                            const std::optional<components::OnMouseMoved>& component);
};
}  // namespace rtype::client::systems
