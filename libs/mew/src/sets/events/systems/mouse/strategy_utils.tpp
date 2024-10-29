/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MouseStrategyUtils.hpp
*/

#pragma once

#include <iostream>

namespace mew::sets::events {
template <typename MouseEventComponent>
MouseEventTarget MouseStrategyUtils::GetCurrentTarget(
    const sf::Vector2f &mouse, const MouseEventComponent &component,
    const sparse_array<drawable::Drawable>::ptr &drawables, std::size_t entityId) {
  auto emptyDrawable = std::optional<drawable::Drawable>();
  auto &drawable = drawables->size() > entityId ? (*drawables)[entityId] : emptyDrawable;
  auto is_inside = drawable->bounds.contains(mouse);

  if (!drawable && component.strategy == MouseEventTarget::kAnyTarget) {
    return kAnyTarget;
  } else if (!drawable) {
    std::cerr << "No drawable component found for entity " << entityId
              << " . Localized mouse strategy ignored." << std::endl;
    return kNoTarget;
  } else if ((component.strategy & kLocalTarget) == kLocalTarget && is_inside) {
    return MouseEventTarget::kLocalTarget;
  } else if ((component.strategy & kOtherTarget) == kOtherTarget && !is_inside) {
    return MouseEventTarget::kOtherTarget;
  } else {
    return MouseEventTarget::kNoTarget;
  }
}
}  // namespace mew::sets::events
