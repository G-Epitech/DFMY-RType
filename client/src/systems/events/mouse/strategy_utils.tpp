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

template <typename MouseEventComponent>
events::MouseEventTarget MouseStrategyUtils::GetCurrentTarget(
    const sf::Vector2f &mouse, const MouseEventComponent &component,
    const sparse_array<components::Drawable>::ptr &drawables, std::size_t entityId) {
  auto emptyDrawable = std::optional<components::Drawable>();
  auto &drawable = drawables->size() > entityId ? (*drawables)[entityId] : emptyDrawable;
  auto is_inside = drawable->bounds.contains(mouse);

  if (!drawable && component.strategy == events::MouseEventTarget::kAnyTarget) {
    return events::kAnyTarget;
  } else if (!drawable) {
    std::cerr << "No drawable component found for entity " << entityId
              << " . Localized mouse strategy ignored." << std::endl;
    return events::kNoTarget;
  } else if ((component.strategy & events::kLocalTarget) == events::kLocalTarget && is_inside) {
    return events::MouseEventTarget::kLocalTarget;
  } else if ((component.strategy & events::kOtherTarget) == events::kOtherTarget && !is_inside) {
    return events::MouseEventTarget::kOtherTarget;
  } else {
    return events::MouseEventTarget::kNoTarget;
  }
}
