/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

namespace rtype::client::components {

/// @brief Align Horizontally Component use in an ECS
enum class HorizontalAlign {
  LEFT,    ///< Left align
  CENTER,  ///< Center align
  RIGHT,   ///< Right align
};

/// @brief Align Vertically Component use in an ECS
enum class VerticalAlign {
  TOP,     ///< Top align
  CENTER,  ///< Center align
  BOTTOM,  ///< Bottom align
};

/// @brief Position Component use in an ECS
struct Position {
  float x = 0;                                              ///< X position
  float y = 0;                                              ///< Y position
  HorizontalAlign horizontalAlign = HorizontalAlign::LEFT;  ///< Horizontal align
  VerticalAlign verticalAlign = VerticalAlign::TOP;         ///< Vertical align
};
}  // namespace rtype::client::components
