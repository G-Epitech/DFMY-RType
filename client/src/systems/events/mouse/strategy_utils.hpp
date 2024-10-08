/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MouseStrategyUtils.hpp
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "components/position.hpp"
#include "libs/zygarde/src/core/components/transform/transform.hpp"
#include "libs/zygarde/src/tools/spare_array.hpp"

namespace rtype::client::systems {
class MouseStrategyUtils {
 public:
  /**
   * @brief Get the current target of the event
   * @param mouse Mouse position
   * @param component Component to get the strategy from
   * @param drawables Drawables to get the bounds from
   * @param entityId Entity id to get the position from
   */
  template <typename MouseEventComponent, typename SFMLMouseType>
  static events::MouseEventTarget GetCurrentTarget(
      const SFMLMouseType &mouse, const MouseEventComponent &component,
      const sparse_array<components::Drawable>::ptr &drawables, std::size_t entityId);
};
}  // namespace rtype::client::systems

#include "strategy_utils.tpp"
