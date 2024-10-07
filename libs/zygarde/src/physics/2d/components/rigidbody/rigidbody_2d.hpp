/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rigidbody2D.hpp
*/

#pragma once

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_2f.hpp"

namespace zygarde::physics::components {
class EXPORT_ZYGARDE_API Rigidbody2D final {
 public:
  Rigidbody2D() = default;
  ~Rigidbody2D() = default;

  Rigidbody2D &operator=(const Rigidbody2D &other) = delete;
  Rigidbody2D &operator=(Rigidbody2D &&other) noexcept = delete;

 public:
  /**
   * @brief Add force to the Rigidbody2D object
   * @param force vector_2f object
   */
  void AddForce(core::types::vector_2f force) noexcept;

  /**
   * @brief Add force to the Rigidbody2D object
   * @param x x value
   * @param y y value
   */
  void AddForce(float x, float y) noexcept;

  /**
   * @brief Get velocity of the Rigidbody2D object
   * @param velocity vector_2f object
   */
  [[nodiscard]] inline const core::types::vector_2f &GetVelocity() const noexcept {
    return velocity_;
  }

 private:
  /// @brief Velocity vector
  core::types::vector_2f velocity_;
};
}  // namespace zygarde::physics::components
