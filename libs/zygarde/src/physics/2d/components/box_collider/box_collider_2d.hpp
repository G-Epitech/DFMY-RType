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
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param on_collision_enter On collision enter function callback
   * @param on_collision_exit On collision exit function callback
   */
  BoxCollider2D(const core::types::Vector2f &size, Rigidbody2D *attached_rigidbody,
                Collision2DFunction on_collision_enter, Collision2DFunction on_collision_exit);

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param collision_layers Collision layers
   * @param on_collision_enter On collision enter function callback
   * @param on_collision_exit On collision exit function callback
   */
  BoxCollider2D(const core::types::Vector2f &size, Rigidbody2D *attached_rigidbody,
                std::vector<int> collision_layers, Collision2DFunction on_collision_enter,
                Collision2DFunction on_collision_exit);

 public:
  /**
   * @brief Get the size of the box
   */
  [[nodiscard]] inline const core::types::Vector2f &GetSize() const noexcept { return size_; }

  /**
   * @brief Set the size of the box
   */
  void SetSize(const core::types::Vector2f &size);

  /**
   * @brief Execute the OnCollisionEnter function callback from the Collider2D object
   * @param collision_2d Current collision
   */
  inline void OnCollisionEnter(Collision2D *collision_2d) const noexcept {
    collider_.onCollisionEnter_(collision_2d);
  }

  /**
   * @brief Execute the OnCollisionExit function callback from the Collider2D object
   * @param collision_2d Current collision
   */
  inline void OnCollisionExit(Collision2D *collision_2d) const noexcept {
    collider_.onCollisionExit_(collision_2d);
  }

 private:
  /// @brief Size of the box
  core::types::Vector2f size_;
  /// @brief Collider2D object
  Collider2D collider_;
};
}  // namespace zygarde::physics::components
