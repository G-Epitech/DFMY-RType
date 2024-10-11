/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.cpp
*/

#include "collider_2d.hpp"

#include <algorithm>
#include <utility>

using namespace zygarde::physics::components;

Collider2D::Collider2D(std::shared_ptr<Rigidbody2D> attached_rigidbody,
                       std::vector<int> collision_layers, const core::types::Vector2f &position)
    : attachedRigidbody_(std::move(attached_rigidbody)),
      collisionLayers_(std::move(collision_layers)),
      position_(position), collisionQueue_() {}

Collider2D::Collider2D(std::shared_ptr<Rigidbody2D> attached_rigidbody,
                       const core::types::Vector2f &position)
    : attachedRigidbody_(std::move(attached_rigidbody)),
      collisionLayers_(),
      position_(position), collisionQueue_() {}
