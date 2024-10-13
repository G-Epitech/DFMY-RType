/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.cpp
*/

#include "./collider_2d.hpp"

#include <algorithm>
#include <utility>

using namespace zygarde::physics::components;

Collider2D::Collider2D(std::vector<int> collision_layers)
    : collisionLayers_(std::move(collision_layers)), collisionQueue_() {}

zygarde::physics::types::Collision2D::ptr Collider2D::GetNextCollision() noexcept {
  auto collision = collisionQueue_.front();
  collisionQueue_.pop();
  return collision;
}
