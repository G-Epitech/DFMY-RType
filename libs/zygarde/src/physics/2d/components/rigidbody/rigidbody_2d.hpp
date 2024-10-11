/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rigidbody2D.hpp
*/

#pragma once

#include <memory>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_2f.hpp"

namespace zygarde::physics::components {
class EXPORT_ZYGARDE_API Rigidbody2D final {
 public:
  using ptr = std::shared_ptr<Rigidbody2D>;
  using const_ptr = std::shared_ptr<const Rigidbody2D>;

 public:
  Rigidbody2D() = default;
  ~Rigidbody2D() = default;

  /**
   * @brief Construct a new Rigidbody2D object
   * @param velocity The applied velocity to the Rigidbody2D object
   */
  explicit Rigidbody2D(core::types::Vector2f velocity) noexcept;

 public:
  /**
   * @brief Add force to the Rigidbody2D object
   * @param force Vector2f object
   */
  void AddForce(core::types::Vector2f force) noexcept;

  /**
   * @brief Add force to the Rigidbody2D object
   * @param x x value
   * @param y y value
   */
  void AddForce(float x, float y) noexcept;

  /**
   * @brief Get velocity of the Rigidbody2D object
   * @param velocity Vector2f object
   */
  [[nodiscard]] inline const core::types::Vector2f &GetVelocity() const noexcept {
    return velocity_;
  }

 private:
  /// @brief Velocity vector
  core::types::Vector2f velocity_;
};
}  // namespace zygarde::physics::components
