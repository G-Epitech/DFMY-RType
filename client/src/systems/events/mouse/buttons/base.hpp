/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base.hpp
*/

#pragma once

#include "components/on_event.hpp"
#include "components/position.hpp"
#include "systems/events/base.hpp"

namespace rtype::client::systems {
template <events::EventType EventType, typename MouseEventComponent>
class MouseEventSystemBase : public EventSystemBase<EventType, MouseEventComponent> {
 public:
  /**
   * @brief Build a new Mouse Event System Base object
   * @param window_manager Window Manager to use
   */
  explicit MouseEventSystemBase(WindowManager::Ptr window_manager);

  ~MouseEventSystemBase() = default;

 protected:
  void HandleEvent(const sf::Event &event, Registry::Ptr r,
                   const sparse_array<MouseEventComponent> &components) final;

  /**
   * @brief Check if the strategy is the same as the target
   * @param strategy Strategy to check
   * @param target Target strategy
   * @return Comparison result
   */
  static bool IsStrategy(events::MouseEventStrategy strategy,
                         events::MouseEventStrategy target) noexcept;

  /**
   * @brief Handle the local strategy of the mouse press event
   * @param event Event to handle
   * @param component Component to handle
   * @param positions Positions of the entities
   * @param entityId Entity id
   */
  static void HandleLocalizedStrategy(const sf::Event &event, const MouseEventComponent &component,
                                      const sparse_array<components::Position> &positions,
                                      std::size_t entityId);
};
}  // namespace rtype::client::systems

#include "base.tpp"
