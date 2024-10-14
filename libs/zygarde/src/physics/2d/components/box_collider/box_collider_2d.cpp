/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.cpp
*/

#include "./box_collider_2d.hpp"

#include <utility>

using namespace zygarde::physics::components;

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size) : size_(size), collider_() {
  core::types::Vector2f::throw_if_negative(size);
}

BoxCollider2D::BoxCollider2D(const core::types::Vector2f& size, std::vector<int> collision_layers)
    : size_(size), collider_(std::move(collision_layers)) {
  core::types::Vector2f::throw_if_negative(size);
}

void BoxCollider2D::SetSize(const core::types::Vector2f& size) {
  core::types::Vector2f::throw_if_negative(size);
  size_ = size;
}

void BoxCollider2D::AddCollision(types::Collision2D collision) noexcept {
  collider_.collisionQueue_.push(std::make_shared<types::Collision2D>(collision));
}
