/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collision_2d.hpp
*/

#pragma once

#include <memory>

#include "libs/zygarde/src/core/components/transform/transform.hpp"
#include "libs/zygarde/src/physics/2d/components/rigidbody/rigidbody_2d.hpp"

namespace zygarde::physics::types {
/// @brief Collision2D struct passed to the collision callback
struct Collision2D {
  /// @brief Pointer to the Collision2D
  using ptr = std::shared_ptr<Collision2D>;
  /// @brief Pointer to the Rigidbody2D of the current entity
  components::Rigidbody2D *myRigidbody;
  /// @brief Pointer to the Transform of the current entity
  core::components::Transform *myTransform;
  /// @brief Rigidbody2D of the other colliding entity
  const components::Rigidbody2D *otherRigidbody;
  /// @brief Transform of the other colliding entity
  const core::components::Transform *otherTransform;
};

/// @brief Colliding callback function
using Collision2DFunction = std::function<void(const Collision2D::ptr &)>;
}  // namespace zygarde::physics::types
