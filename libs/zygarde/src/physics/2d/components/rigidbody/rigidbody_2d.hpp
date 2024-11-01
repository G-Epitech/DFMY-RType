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

  /**
   * @brief Construct a new Rigidbody2D object
   * @param velocity Velocity to apply
   * @param isKinematic Is the Rigidbody2D object kinematic
   * @param drag Drag value
   */
  Rigidbody2D(core::types::Vector2f velocity, bool isKinematic, float drag) noexcept;

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
  [[nodiscard]] const core::types::Vector2f &GetVelocity() const noexcept { return velocity_; }

  /**
   * @brief Set velocity of the Rigidbody2D object
   * @param velocity Velocity to set
   */
  void SetVelocity(const core::types::Vector2f &velocity) noexcept { velocity_ = velocity; }

  /**
   * @brief Get the velocity of the Rigidbody2D object
   */
  [[nodiscard]] inline core::types::Vector2f GetVelocity() noexcept { return velocity_; }

  /**
   * @brief Set the velocity of the Rigidbody2D object To zero
   */
  constexpr void CancelVelocity() noexcept { velocity_ = core::types::Vector2f::zero(); }

  /**
   * @brief Set the rigidbody to kinematic or not
   */
  void SetKinematic(bool isKinematic) noexcept { isKinematic_ = isKinematic; }

  /**
   * @brief Check if the rigidbody is kinematic
   */
  [[nodiscard]] bool IsKinematic() const noexcept { return isKinematic_; }

  /**
   * @brief Set the drag value of the Rigidbody2D object
   */
  inline void SetDrag(float drag) noexcept { drag_ = drag; }

  /**
   * @brief Get the drag value of the Rigidbody2D object
   */
  [[nodiscard]] inline float GetDrag() const noexcept { return drag_; }

  /**
   * @brief Set the movement offset of the Rigidbody2D object
   */
  inline void SetMovementOffset(const core::types::Vector2f &movementOffset) noexcept {
    movementOffset_ = movementOffset;
  }

  /**
   * @brief Get the movement offset of the Rigidbody2D object
   */
  [[nodiscard]] inline const core::types::Vector2f &GetMovementOffset() const noexcept {
    return movementOffset_;
  }

 private:
  /// @brief Velocity vector
  core::types::Vector2f velocity_;
  /// @brief Is kinematic flag. Rigidbody will not be affected by physics (force, collisions,etc...)
  /// if set to true
  bool isKinematic_{false};
  /// @brief Drag value
  float drag_{1.0f};
  /// @brief Computed movement offset
  core::types::Vector2f movementOffset_{core::types::Vector2f::zero()};
};
}  // namespace zygarde::physics::components
