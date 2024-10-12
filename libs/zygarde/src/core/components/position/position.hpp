/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** position.hpp
*/

#pragma once

#include "core/types/vector/vector.hpp"

namespace zygarde::core::components {

/// @brief Horizontal align values
enum class HorizontalAlign {
  kLeft,    ///< Left align
  kCenter,  ///< Center align
  kRight,   ///< Right align
};

/// @brief Vertical align values
enum class VerticalAlign {
  kTop,     ///< Top align
  kCenter,  ///< Center align
  kBottom,  ///< Bottom align
};

/// @brief Aligns component
struct Alignment {
  HorizontalAlign horizontal = HorizontalAlign::kLeft;  ///< Horizontal align
  VerticalAlign vertical = VerticalAlign::kTop;         ///< Vertical align
};

/// @brief Position component
struct Position {
  core::types::Vector3f point;  ///< Position point
  Alignment aligns;             ///< Aligns
};
}  // namespace zygarde::core::components
