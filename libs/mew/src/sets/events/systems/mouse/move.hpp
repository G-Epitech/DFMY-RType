/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** move.hpp
*/

#pragma once

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/systems/system_base.hpp"

namespace mew::sets::events {
class MouseMoveEventSystem : public EventSystemBase<kMouseMoved, OnMouseMoved> {
 public:
  /**
   * @brief Construct a new Mouse Move Event System object
   * @param window_manager Window manager to use
   */
  explicit MouseMoveEventSystem(managers::WindowManager::Ptr window_manager);

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   zipper<OnMouseMoved> components) override;
  /**
   * @brief Handle the event for the entity
   * @param entityId Entity id
   * @param event Event to handle
   * @param drawables Drawables components
   * @param component Component to handle
   */
  void HandleEventForEntity(std::size_t entityId, const sf::Event& event,
                            const sparse_array<drawable::Drawable>::ptr& drawables,
                            const OnMouseMoved& component);
};
}  // namespace mew::sets::events
