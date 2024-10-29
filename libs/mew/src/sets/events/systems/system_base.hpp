/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** event_system_base.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "libs/mew/include/api.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/mew/src/sets/events/constants.hpp"
#include "libs/zygarde/src/system_abstract.hpp"

namespace mew::sets::events {
template <EventType, class... Components>
class EXPORT_MEW_API EventSystemBase : public ASystem<Components...> {
 public:
  ~EventSystemBase() override = default;

  /**
   * @brief Run the system
   * @param r Registry to use
   * @param components Components to use
   */
  void Run(Registry::Ptr r, zipper<Components...> components) final;

 protected:
  /**
   * @brief Construct a new Event System Base object
   * @param event_deferrer Event deferrer to encapsulate
   */
  explicit EventSystemBase(managers::WindowManager::Ptr window_manager);

  /// @brief Window manager
  managers::WindowManager::Ptr windowManager_;

  /**
   * @brief Handle logic for current event
   * @param event Event to handle
   * @param r Registry to use
   * @param components Components to use
   */
  virtual void HandleEvent(const sf::Event &event, Registry::Ptr r,
                           zipper<Components...> components) = 0;
};
}  // namespace mew::sets::events

#include "./system_base.tpp"
