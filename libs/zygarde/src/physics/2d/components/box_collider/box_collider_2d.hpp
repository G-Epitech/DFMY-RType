/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.hpp
*/

#pragma once

#include <stdexcept>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_2f.hpp"
#include "physics/2d/components/collider/collider_2d.hpp"

namespace zygarde::physics::components {
class EXPORT_ZYGARDE_API BoxCollider2D final {
 public:
  BoxCollider2D() = delete;
  ~BoxCollider2D() = default;

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param attachedRigidbody Reference to the attached Rigidbody2D object
   * @param onCollisionEnter On collision enter function callback
   * @param onCollisionExit On collision exit function callback
   */
  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                Collision2DFunction onCollisionEnter, Collision2DFunction onCollisionExit);

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param attachedRigidbody Reference to the attached Rigidbody2D object
   * @param collisionLayers Collision layers
   * @param onCollisionEnter On collision enter function callback
   * @param onCollisionExit On collision exit function callback
   */
  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                std::vector<int> collisionLayers, Collision2DFunction onCollisionEnter,
                Collision2DFunction onCollisionExit);

 public:
  /**
   * @brief Get the size of the box
   */
  [[nodiscard]] inline const core::types::vector_2f &GetSize() const noexcept { return size_; }

  /**
   * @brief Set the size of the box
   */
  void SetSize(const core::types::vector_2f &size);

  /**
   * @brief Execute the OnCollisionEnter function callback from the Collider2D object
   */
  inline void OnCollisionEnter(Collision2D &collision2D) const noexcept {
    collider_.onCollisionEnter_(collision2D);
  }

  /**
   * @brief Execute the OnCollisionExit function callback from the Collider2D object
   */
  inline void OnCollisionExit(Collision2D &collision2D) const noexcept {
    collider_.onCollisionExit_(collision2D);
  }

 private:
  /// @brief Size of the box
  core::types::vector_2f size_;
  /// @brief Collider2D object
  Collider2D collider_;
};
}  // namespace zygarde::physics::components
