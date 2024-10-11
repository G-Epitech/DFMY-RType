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
   */
  BoxCollider2D(const core::types::Vector2f &size, const core::types::Vector2f &position,
                Rigidbody2D::ptr attached_rigidbody);

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param collision_layers Collision layers
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

  [[nodiscard]] inline const std::vector<int> &GetCollisionLayers() const noexcept {
    return collider_.collisionLayers_;
  }

  [[nodiscard]] types::BoundingBox2D GetBoundingBox() const noexcept;

  void AddColllision(types::Collision2D collision) noexcept;

 private:
  /// @brief Size of the box
  core::types::Vector2f size_;
  /// @brief Collider2D object
  Collider2D collider_;
};
}  // namespace zygarde::physics::components
