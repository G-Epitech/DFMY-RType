/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "box_collider_2d.hpp"

#include <utility>

using namespace rtype::sdk::ECS::physics::components;
using namespace rtype::sdk::ECS;

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Collider2D collider)
    : size_(size), collider_(std::move(collider)) {}

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             std::vector<int> collisionLayers, CollisionFunction onCollisionEnter,
                             CollisionFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(collisionLayers), std::move(onCollisionEnter),
                std::move(onCollisionExit)) {}

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             CollisionFunction onCollisionEnter, CollisionFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(onCollisionEnter), std::move(onCollisionExit)) {}

const core::types::vector_2f& BoxCollider2D::GetSize() const noexcept {
  return size_;
}
void BoxCollider2D::SetSize(const core::types::vector_2f& size) noexcept {
  size_ = size;
}
