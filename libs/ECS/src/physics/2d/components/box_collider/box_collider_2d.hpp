/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.hpp
*/

#pragma once

#include "libs/ECS/src/core/types/vector/vector_2f.hpp"
#include "physics/2d/components/collider/collider_2d.hpp"

namespace rtype::sdk::ECS::physics::components {
class BoxCollider2D {
 public:
  BoxCollider2D() = delete;
  ~BoxCollider2D() = default;

  BoxCollider2D(const core::types::vector_2f &size, Collider2D collider);

  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                CollisionFunction onCollisionEnter, CollisionFunction onCollisionExit);

  BoxCollider2D(const core::types::vector_2f &size, Rigidbody2D &attachedRigidbody,
                std::vector<int> collisionLayers, CollisionFunction onCollisionEnter,
                CollisionFunction onCollisionExit);

  BoxCollider2D(const BoxCollider2D &other) = default;
  BoxCollider2D &operator=(const BoxCollider2D &other) = default;
  BoxCollider2D(BoxCollider2D &&other) noexcept = default;
  BoxCollider2D &operator=(BoxCollider2D &&other) noexcept = default;

 public:
  [[nodiscard]] const core::types::vector_2f &GetSize() const noexcept;
  void SetSize(const core::types::vector_2f &size) noexcept;

 public:
  CollisionFunction onCollisionEnter;
  CollisionFunction onCollisionExit;

 private:
  core::types::vector_2f size_;
  Collider2D collider_;
};
}  // namespace rtype::sdk::ECS::physics::components
