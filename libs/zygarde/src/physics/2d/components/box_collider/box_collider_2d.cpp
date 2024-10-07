/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "box_collider_2d.hpp"

#include <utility>

using namespace zygarde::physics::components;

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             std::vector<int> collisionLayers, Collision2DFunction onCollisionEnter,
                             Collision2DFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(collisionLayers), std::move(onCollisionEnter),
                std::move(onCollisionExit)) {
  core::types::vector_2f::throw_if_negative(size);
}

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             Collision2DFunction onCollisionEnter,
                             Collision2DFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(onCollisionEnter), std::move(onCollisionExit)) {
  core::types::vector_2f::throw_if_negative(size);
}

void BoxCollider2D::SetSize(const core::types::vector_2f& size) {
  core::types::vector_2f::throw_if_negative(size);
  size_ = size;
}
