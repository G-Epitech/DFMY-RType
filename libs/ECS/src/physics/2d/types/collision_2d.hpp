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
/// @brief Collision2D struct passed to the collision callback
struct Collision2D {
  /// @brief Rigidbody2D of the current entity
  Rigidbody2D &myRigidbody;
  /// @brief Transform2D of the current entity
  core::components::Transform2D &myTransform;
  /// @brief Rigidbody2D of the other colliding entity
  const Rigidbody2D &otherRigidbody;
  /// @brief Transform2D of the other colliding entity
  const core::components::Transform2D &otherTransform;
};

/// @brief Colliding callback function
using Collision2DFunction = std::function<void(Collision2D &)>;
}  // namespace rtype::sdk::ECS::physics::components
