/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BoundingBox2DBuilder.hpp
*/

#pragma once

#include "bounding_box_2d.hpp"
#include "core/components/position/position.hpp"
#include "core/types/vector/vector_2f.hpp"

namespace zygarde::physics::types {
class BoundingBox2DBuilder {
 public:
  BoundingBox2DBuilder() = delete;
  ~BoundingBox2DBuilder() = default;

 public:
  static BoundingBox2D build(const core::components::Position &position,
                             const core::types::Vector2f &size) noexcept;

 private:
  static void ResolveVerticalBounds(const zygarde::core::components::Position &position,
                                    BoundingBox2D *bounding_box,
                                    zygarde::core::types::Vector2f size) noexcept;

  static void ResolveHorizontalBounds(const zygarde::core::components::Position &position,
                                      BoundingBox2D *bounding_box,
                                      zygarde::core::types::Vector2f size) noexcept;
};
}  // namespace zygarde::physics::types
