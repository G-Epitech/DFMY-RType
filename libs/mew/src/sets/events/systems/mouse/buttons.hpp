/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/mew/src/sets/events/constants.hpp"

namespace mew::sets::events {
template <EventType EventType, typename MouseEventComponent>
class MouseButtonEventSystem
    : public EventSystemBase<EventType, MouseEventComponent, drawable::Drawable> {
 public:
  /**
   * @brief Build a new Mouse Event System Base object
   * @param window_manager Window Manager to use
   */
  explicit MouseButtonEventSystem(managers::WindowManager::Ptr window_manager);

  ~MouseButtonEventSystem() override = default;

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   typename sparse_array<MouseEventComponent>::ptr components,
                   sparse_array<drawable::Drawable>::ptr drawables) override;

  /**
   * @brief Handle the event for the entity
   * @param entityId Entity id
   * @param event Event to handle
   * @param drawables Drawables components
   * @param component Component to handle
   */
  void HandleEventForEntity(std::size_t entityId, const sf::Event& event,
                            const sparse_array<drawable::Drawable>::ptr& drawables,
                            const std::optional<MouseEventComponent>& component);
};

typedef MouseButtonEventSystem<kMouseReleased, OnMouseReleased> MouseReleaseEventSystem;

typedef MouseButtonEventSystem<kMousePressed, OnMousePressed> MousePressEventSystem;

}  // namespace mew::sets::events

#include "./buttons.tpp"
