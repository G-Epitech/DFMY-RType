/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** transform.hpp
*/

#pragma once

#include "libs/ECS/src/api.hpp"
#include "libs/ECS/src/core/types/vector/vector_2f.hpp"

namespace rtype::sdk::ECS::core::components {
class EXPORT_ECS_SDK_API Transform2D {
 public:
  Transform2D() = default;
  ~Transform2D() = default;

  Transform2D(float x, float y, float scale_x, float scale_y, float rotation);

  Transform2D(const types::vector_2f &position, const types::vector_2f &scale, float rotation);

  Transform2D(const Transform2D &transform) = default;
  Transform2D(Transform2D &&transform) noexcept = default;

 public:
  types::vector_2f position;
  types::vector_2f scale;
  float rotation;
};
}  // namespace rtype::sdk::ECS::core::components
