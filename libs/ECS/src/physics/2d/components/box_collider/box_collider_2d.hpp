/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.hpp
*/

#pragma once

#include <cassert>

#include "libs/ECS/src/api.hpp"
#include "libs/ECS/src/core/types/vector/vector_2f.hpp"
#include "physics/2d/components/collider/collider_2d.hpp"

namespace rtype::sdk::ECS::physics::components {
class EXPORT_ECS_SDK_API BoxCollider2D final {
 public:
  BoxCollider2D() = delete;
  ~BoxCollider2D() = default;

  BoxCollider2D(const core::types::vector_2f &size, Collider2D collider);

  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                Collision2DFunction onCollisionEnter, Collision2DFunction onCollisionExit);

  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                std::vector<int> collisionLayers, Collision2DFunction onCollisionEnter,
                Collision2DFunction onCollisionExit);

  BoxCollider2D(const BoxCollider2D &other) = default;
  BoxCollider2D(BoxCollider2D &&other) noexcept = default;

 public:
  [[nodiscard]] inline const core::types::vector_2f &GetSize() const noexcept { return size_; }

  inline void SetSize(const core::types::vector_2f &size) noexcept {
    assert(size.x > 0 && size.y > 0 && "Box size should be positive");
    size_ = size;
  }

  [[nodiscard]] inline const Collision2DFunction &OnCollisionEnter() const noexcept {
    return collider_.onCollisionEnter_;
  }

  [[nodiscard]] inline const Collision2DFunction &OnCollisionExit() const noexcept {
    return collider_.onCollisionExit_;
  }

 private:
  core::types::vector_2f size_;
  Collider2D collider_;
};
}  // namespace rtype::sdk::ECS::physics::components
