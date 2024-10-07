/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collision_2d.hpp
*/

#pragma once

#include "libs/ECS/src/core/components/transform/transform_2d.hpp"
#include "libs/ECS/src/physics/2d/components/rigidbody/rigidbody_2d.hpp"

namespace rtype::sdk::ECS::physics::components {
struct Collision2D {
  const Rigidbody2D &otherRigidbody;
  const core::components::Transform2D &otherTransform;
};

using CollisionFunction = std::function<void(Collision2D &)>;
}  // namespace rtype::sdk::ECS::physics::components
