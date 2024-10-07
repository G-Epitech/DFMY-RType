/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.cpp
*/

#include "collider_2d.hpp"

#include <utility>

using namespace rtype::sdk::ECS::physics::components;

Collider2D::Collider2D(Rigidbody2D &attachedRigidbody, std::vector<int> collisionLayers,
                       Collision2DFunction onCollisionEnter, Collision2DFunction onCollisionExit)
    : attachedRigidbody_(attachedRigidbody),
      collisionLayers_(std::move(collisionLayers)),
      onCollisionEnter_(std::move(onCollisionEnter)),
      onCollisionExit_(std::move(onCollisionExit)) {}

Collider2D::Collider2D(Rigidbody2D &attachedRigidbody, Collision2DFunction onCollisionEnter,
                       Collision2DFunction onCollisionExit)
    : attachedRigidbody_(attachedRigidbody),
      collisionLayers_(constants::kDefaultCollisionLayers),
      onCollisionEnter_(std::move(onCollisionEnter)),
      onCollisionExit_(std::move(onCollisionExit)) {}
