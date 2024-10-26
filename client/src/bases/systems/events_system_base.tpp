/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** event_system_base.hpp
*/

#pragma once

#include "components/on_event.hpp"

using namespace rtype::client;
using namespace rtype::client::systems;

template <events::EventType EventType, class... EventComponents>
EventSystemBase<EventType, EventComponents...>::EventSystemBase(WindowManager::Ptr window_manager)
    : ASystem<EventComponents...>() {
  windowManager_ = std::move(window_manager);
}

template <events::EventType EventType, class... EventComponents>
void EventSystemBase<EventType, EventComponents...>::Run(
    Registry::Ptr r, sparse_array<EventComponents>::ptr... components) {
  auto type_to_handle = events::EventTypeMapper<EventType>::type;
  auto& events = windowManager_->GetDeferredEvents();

  for (const auto& event : events) {
    if (event.type == type_to_handle)
      HandleEvent(event, r, components...);
  }
}
