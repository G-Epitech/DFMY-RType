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
  Rigidbody2D &myRigidbody;
  core::components::Transform2D &myTransform;
  const Rigidbody2D &otherRigidbody;
  const core::components::Transform2D &otherTransform;
};

using Collision2DFunction = std::function<void(Collision2D &)>;
}  // namespace rtype::sdk::ECS::physics::components
