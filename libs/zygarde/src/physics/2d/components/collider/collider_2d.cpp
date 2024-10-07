/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.cpp
*/

#include "collider_2d.hpp"

#include <utility>

using namespace zygarde::physics::components;

Collider2D::Collider2D(Rigidbody2D *attached_rigidbody, std::vector<int> collision_layers,
                       Collision2DFunction on_collision_enter,
                       Collision2DFunction on_collision_exit)
    : attachedRigidbody_(attached_rigidbody),
      collisionLayers_(std::move(collision_layers)),
      onCollisionEnter_(std::move(on_collision_enter)),
      onCollisionExit_(std::move(on_collision_exit)) {}

Collider2D::Collider2D(Rigidbody2D *attached_rigidbody, Collision2DFunction on_collision_enter,
                       Collision2DFunction on_collision_exit)
    : attachedRigidbody_(attached_rigidbody),
      collisionLayers_(constants::kDefaultCollisionLayers),
      onCollisionEnter_(std::move(on_collision_enter)),
      onCollisionExit_(std::move(on_collision_exit)) {}
