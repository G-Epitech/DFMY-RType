/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MouseStrategyUtils.hpp
*/

#pragma once

#include <iostream>

#include "components/on_event.hpp"

using namespace rtype::client;
using namespace rtype::client::systems;

template <typename MouseEventComponent, typename SFMLMouseType>
events::MouseEventTarget MouseStrategyUtils::GetCurrentTarget(
    const SFMLMouseType &mouse, const MouseEventComponent &component,
    const sparse_array<components::Drawable>::ptr &drawables, std::size_t entityId) {
  auto drawable =
      drawables->size() > entityId ? (*drawables)[entityId] : std::optional<components::Drawable>();
  auto is_inside =
      drawable->bounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

  if (component.strategy == events::MouseEventTarget::kAnyTarget) {
    return events::kAnyTarget;
  } else if (!drawable) {
    std::cerr << "No drawable component found for entity " << entityId
              << " . Localized mouse strategy ignored." << std::endl;
    return events::kNoTarget;
  } else if (component.strategy == events::MouseEventTarget::kLocalTarget && is_inside) {
    return events::MouseEventTarget::kLocalTarget;
  } else if (component.strategy == events::MouseEventTarget::kOtherTarget && !is_inside) {
    return events::MouseEventTarget::kOtherTarget;
  } else {
    return events::MouseEventTarget::kNoTarget;
  }
}
