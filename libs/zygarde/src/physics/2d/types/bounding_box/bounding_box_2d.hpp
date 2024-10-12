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
struct BoundingBox2D {
  float left = 0;
  float right = 0;
  float top = 0;
  float bottom = 0;
};
}  // namespace zygarde::physics::types
