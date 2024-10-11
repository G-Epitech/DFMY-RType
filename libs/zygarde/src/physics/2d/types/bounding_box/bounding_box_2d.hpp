/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** bounding_box_2d.hpp
*/

#pragma once

#include "core/types/vector/vector_2f.hpp"

namespace zygarde::physics::types {
struct BoundingBox2D {
  float left;
  float right;
  float top;
  float bottom;

  BoundingBox2D(core::types::Vector2f position, core::types::Vector2f size);
};
}  // namespace zygarde::physics::types
