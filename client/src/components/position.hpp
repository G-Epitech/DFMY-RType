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
  kLeft,    ///< Left align
  kCenter,  ///< Center align
  kRight,   ///< Right align
};

/// @brief Align Vertically Component use in an ECS
enum class VerticalAlign {
  kTop,     ///< Top align
  kCenter,  ///< Center align
  kBottom,  ///< Bottom align
};

/// @brief Position Component use in an ECS
struct Position {
  float x = 0;                                               ///< X position
  float y = 0;                                               ///< Y position
  HorizontalAlign horizontalAlign = HorizontalAlign::kLeft;  ///< Horizontal align
  VerticalAlign verticalAlign = VerticalAlign::kTop;         ///< Vertical align
};
}  // namespace rtype::client::components
