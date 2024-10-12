/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "./box_collider_2d.hpp"

#include <utility>

using namespace zygarde::physics::components;

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size,
                             std::shared_ptr<Rigidbody2D> attached_rigidbody,
                             std::vector<int> collision_layers,
                             Collision2DFunction on_collision_enter,
                             Collision2DFunction on_collision_exit)
    : size_(size),
      collider_(std::move(attached_rigidbody), std::move(collision_layers),
                std::move(on_collision_enter), std::move(on_collision_exit)) {
  core::types::Vector2f::throw_if_negative(size);
}

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size,
                             std::shared_ptr<Rigidbody2D> attached_rigidbody,
                             Collision2DFunction on_collision_enter,
                             Collision2DFunction on_collision_exit)
    : size_(size),
      collider_(std::move(attached_rigidbody), std::move(on_collision_enter),
                std::move(on_collision_exit)) {
  core::types::Vector2f::throw_if_negative(size);
}

void BoxCollider2D::SetSize(const core::types::Vector2f& size) {
  core::types::Vector2f::throw_if_negative(size);
  size_ = size;
}
