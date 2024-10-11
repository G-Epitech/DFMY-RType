/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "box_collider_2d.hpp"

#include <utility>

using namespace zygarde::physics::components;

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size,
                             const core::types::Vector2f& position,
                             std::shared_ptr<Rigidbody2D> attached_rigidbody)
    : size_(size), collider_(std::move(attached_rigidbody), position) {
  core::types::Vector2f::throw_if_negative(size);
}

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size,
                             const core::types::Vector2f& position,
                             std::shared_ptr<Rigidbody2D> attached_rigidbody,
                             std::vector<int> collision_layers)
    : size_(size), collider_(std::move(attached_rigidbody), std::move(collision_layers), position) {
  core::types::Vector2f::throw_if_negative(size);
}

void BoxCollider2D::SetSize(const core::types::Vector2f& size) {
  core::types::Vector2f::throw_if_negative(size);
  size_ = size;
}

inline void BoxCollider2D::OnCollisionExit(const Collision2D::ptr& collision_2d) const noexcept {
  if (collider_.onCollisionExit_.has_value()) {
    collider_.onCollisionExit_.value()(collision_2d);
  }
}

inline void BoxCollider2D::OnCollisionEnter(const Collision2D::ptr& collision_2d) const noexcept {
  if (collider_.onCollisionEnter_.has_value()) {
    collider_.onCollisionEnter_.value()(collision_2d);
  }
}

zygarde::physics::types::BoundingBox2D BoxCollider2D::GetBoundingBox() const noexcept {
  return {collider_.position_, size_};
}
