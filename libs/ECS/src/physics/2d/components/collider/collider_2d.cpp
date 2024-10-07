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
                       CollisionFunction onCollisionEnter, CollisionFunction onCollisionExit)
    : attachedRigidbody_(attachedRigidbody),
      collisionLayers_(std::move(collisionLayers)),
      onCollisionEnter(std::move(onCollisionEnter)),
      onCollisionExit(std::move(onCollisionExit)) {}

Collider2D::Collider2D(Rigidbody2D &attachedRigidbody, CollisionFunction onCollisionEnter,
                       CollisionFunction onCollisionExit)
    : attachedRigidbody_(attachedRigidbody),
      collisionLayers_(constants::kDefaultCollisionLayers),
      onCollisionEnter(std::move(onCollisionEnter)),
      onCollisionExit(std::move(onCollisionExit)) {}
