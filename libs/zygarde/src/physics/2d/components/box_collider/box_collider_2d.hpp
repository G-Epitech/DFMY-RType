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
#include "physics/2d/types/bounding_box/bounding_box_2d.hpp"

namespace zygarde::physics::components {
class EXPORT_ZYGARDE_API BoxCollider2D final {
 public:
  using ptr = std::shared_ptr<BoxCollider2D>;

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
  BoxCollider2D(const core::types::Vector2f &size, const core::types::Vector2f &position,
                Rigidbody2D::ptr attached_rigidbody);

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param collision_layers Collision layers
   * @param on_collision_enter On collision enter function callback
   * @param on_collision_exit On collision exit function callback
   */
  BoxCollider2D(const core::types::Vector2f &size, const core::types::Vector2f &position,
                Rigidbody2D::ptr attached_rigidbody, std::vector<int> collision_layers);

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
  void OnCollisionEnter(const Collision2D::ptr &collision_2d) const noexcept;

  /**
   * @brief Execute the OnCollisionExit function callback from the Collider2D object
   * @param collision_2d Current collision
   */
  void OnCollisionExit(const Collision2D::ptr &collision_2d) const noexcept;

  /**
   * @brief Set the OnCollisionEnter function callback
   * @param on_collision_enter OnCollisionEnter function callback
   */
  inline void SetOnCollisionEnter(const Collision2DFunction &on_collision_enter) noexcept {
    collider_.onCollisionEnter_ = on_collision_enter;
  }

  /**
   * @brief Set the OnCollisionExit function callback
   * @param on_collision_exit OnCollisionExit function callback
   */
  inline void SetOnCollisionExit(const Collision2DFunction &on_collision_exit) noexcept {
    collider_.onCollisionExit_ = on_collision_exit;
  }

  [[nodiscard]] inline const std::vector<int> &GetCollisionLayers() const noexcept {
    return collider_.collisionLayers_;
  }

  [[nodiscard]] types::BoundingBox2D GetBoundingBox() const noexcept;

 private:
  /// @brief Size of the box
  core::types::Vector2f size_;
  /// @brief Collider2D object
  Collider2D collider_;
};
}  // namespace zygarde::physics::components
