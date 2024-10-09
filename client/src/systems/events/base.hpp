/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** event_system_base.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "components/on_event.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "interfaces/scene_interface.hpp"
#include "window/window_manager.hpp"

namespace rtype::client::systems {
template <events::EventType, class... EventsComponent>
class EventSystemBase : public ASystem<EventsComponent...> {
 public:
  ~EventSystemBase() = default;

  /**
   * @brief Run the system
   * @param r Registry to use
   * @param components Components to use
   */
  void Run(Registry::Ptr r, sparse_array<EventsComponent>::ptr... components) final;

 protected:
  /**
   * @brief Construct a new Event System Base object
   * @param event_deferrer Event deferrer to encapsulate
   */
  explicit EventSystemBase(WindowManager::Ptr window_manager);

  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /**
   * @brief Handle logic for current event
   * @param event Event to handle
   * @param r Registry to use
   * @param components Components to use
   */
  virtual void HandleEvent(const sf::Event &event, Registry::Ptr r,
                           sparse_array<EventsComponent>::ptr... components) = 0;
};
}  // namespace rtype::client::systems

#include "base.tpp"
