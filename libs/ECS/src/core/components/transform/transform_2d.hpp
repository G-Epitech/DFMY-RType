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
class EXPORT_ECS_SDK_API Transform2D final {
 public:
  Transform2D() = default;
  ~Transform2D() = default;

  /**
   * @brief Construct a new Transform2D object
   * @param pos_x x position
   * @param pos_y y position
   * @param scale_x x scale
   * @param scale_y y scale
   * @param rotation rotation
   */
  Transform2D(float pos_x, float pos_y, float scale_x, float scale_y, float rotation);

  /**
   * @brief Construct a new Transform2D object
   * @param position Position vector
   * @param scale Scale vector
   * @param rotation Rotation
   */
  Transform2D(const types::vector_2f &position, const types::vector_2f &scale, float rotation);

 public:
  /// @brief Position vector
  types::vector_2f position;
  /// @brief Scale vector
  types::vector_2f scale;
  /// @brief Rotation
  float rotation{0};
};
}  // namespace rtype::sdk::ECS::core::components
