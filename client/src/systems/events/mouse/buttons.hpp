/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "src/bases/systems/events_system_base.hpp"

namespace rtype::client::systems {
template <events::EventType EventType, typename MouseEventComponent>
class MouseButtonEventSystem
    : public EventSystemBase<EventType, MouseEventComponent, components::Drawable> {
 public:
  /**
   * @brief Build a new Mouse Event System Base object
   * @param window_manager Window Manager to use
   */
  explicit MouseButtonEventSystem(WindowManager::Ptr window_manager);

  ~MouseButtonEventSystem() override = default;

 protected:
  void HandleEvent(const sf::Event& event, Registry::Ptr r,
                   typename sparse_array<MouseEventComponent>::ptr components,
                   sparse_array<components::Drawable>::ptr drawables);

  /**
   * @brief Handle the event for the entity
   * @param entityId Entity id
   * @param event Event to handle
   * @param drawables Drawables components
   * @param component Component to handle
   */
  void HandleEventForEntity(std::size_t entityId, const sf::Event& event,
                            const sparse_array<components::Drawable>::ptr& drawables,
                            const std::optional<MouseEventComponent>& component);
};

typedef MouseButtonEventSystem<events::kMouseReleased, components::OnMouseReleased>
    MouseReleaseEventSystem;

typedef MouseButtonEventSystem<events::kMousePressed, components::OnMousePressed>
    MousePressEventSystem;

}  // namespace rtype::client::systems

#include "buttons.tpp"
