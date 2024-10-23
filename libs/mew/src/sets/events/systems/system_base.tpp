/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** event_system_base.hpp
*/

#pragma once

#include "libs/mew/src/sets/events/constants.hpp"

namespace mew::sets::events {

template <EventType EventType, class... Components>
EventSystemBase<EventType, Components...>::EventSystemBase(
    managers::WindowManager::Ptr window_manager)
    : ASystem<Components...>() {
  windowManager_ = std::move(window_manager);
}

template <EventType EventType, class... EventComponents>
void EventSystemBase<EventType, EventComponents...>::Run(
    Registry::Ptr r, sparse_array<EventComponents>::ptr... components) {
  auto type_to_handle = EventTypeMapper<EventType>::type;
  auto& events = windowManager_->GetDeferredEvents();

  for (const auto& event : events) {
    if (event.type == type_to_handle)
      HandleEvent(event, r, components...);
  }
}
}  // namespace mew::sets::events
