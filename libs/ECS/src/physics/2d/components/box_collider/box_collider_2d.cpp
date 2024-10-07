/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "box_collider_2d.hpp"

#include <cassert>
#include <utility>

using namespace rtype::sdk::ECS::physics::components;
using namespace rtype::sdk::ECS;

[[maybe_unused]] BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size,
                                              Collider2D collider)
    : size_(size), collider_(std::move(collider)) {
  assert(size.x > 0 && size.y > 0 && "Box size should be positive");
}

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             std::vector<int> collisionLayers, Collision2DFunction onCollisionEnter,
                             Collision2DFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(collisionLayers), std::move(onCollisionEnter),
                std::move(onCollisionExit)) {
  assert(size.x > 0 && size.y > 0 && "Box size should be positive");
}

BoxCollider2D::BoxCollider2D(const core::types::vector_2f& size, Rigidbody2D& attachedRigidbody,
                             Collision2DFunction onCollisionEnter,
                             Collision2DFunction onCollisionExit)
    : size_(size),
      collider_(attachedRigidbody, std::move(onCollisionEnter), std::move(onCollisionExit)) {
  assert(size.x > 0 && size.y > 0 && "Box size should be positive");
}
