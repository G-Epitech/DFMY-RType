/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** bounding_box_2d.hpp
*/

#pragma once

#include "core/components/position/position.hpp"
#include "core/types/vector/vector_2f.hpp"

namespace zygarde::physics::types {
/// @brief BoundingBox2D struct
struct BoundingBox2D {
  float left = 0;           ///< Left bound
  float right = 0;          ///< Right bound
  float top = 0;            ///< Top bound
  float bottom = 0;         ///< Bottom bound
};
}  // namespace zygarde::physics::types
