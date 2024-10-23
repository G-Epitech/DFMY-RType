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

Collider2D::Collider2D(std::vector<int> collision_layers, std::vector<int> include_layers)
    : collisionLayers_(std::move(collision_layers)), includeLayers_(std::move(include_layers)) {}

zygarde::physics::types::Collision2D::ptr Collider2D::GetNextCollision() noexcept {
  auto collision = collisionQueue_.front();
  collisionQueue_.pop();
  return collision;
}
