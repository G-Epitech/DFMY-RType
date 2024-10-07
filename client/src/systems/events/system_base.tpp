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

template <events::EventType EventType, class... Components>
EventSystemBase<EventType, Components...>::EventSystemBase(
    WindowManager::Ptr window_manager)
    : ASystem<Components...>() {
  windowManager_ = std::move(window_manager);
}

template <events::EventType EventType, class... Components>
void EventSystemBase<EventType, Components...>::Run(Registry::Ptr r,
                                                    sparse_array<Components>&... components) {
  auto type_to_handle = events::EventTypeMapper<EventType>::type;
  auto &events = windowManager_->GetDeferredEvents();

  for (const auto& event : events) {
    if (event.type == type_to_handle)
      HandleEvent(event, r, components...);
  }
}
