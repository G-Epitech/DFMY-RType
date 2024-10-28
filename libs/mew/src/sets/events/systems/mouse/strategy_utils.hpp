/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MouseStrategyUtils.hpp
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "libs/mew/include/api.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/transform/transform.hpp"
#include "libs/zygarde/src/tools/spare_array.hpp"

namespace mew::sets::events {
class EXPORT_MEW_API MouseStrategyUtils final {
 public:
  /**
   * @brief Get the current target of the event
   * @param mouse Mouse position
   * @param component Component to get the strategy from
   * @param drawables Drawables to get the bounds from
   * @param entityId Entity id to get the position from
   */
  template <typename MouseEventComponent>
  static MouseEventTarget GetCurrentTarget(const sf::Vector2f &mouse,
                                           const MouseEventComponent &component,
                                           const sparse_array<drawable::Drawable>::ptr &drawables,
                                           std::size_t entityId);
};
}  // namespace mew::sets::events

#include "./strategy_utils.tpp"
