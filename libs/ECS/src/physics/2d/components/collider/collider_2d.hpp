/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.hpp
*/

#pragma once

#include <functional>
#include <utility>
#include <vector>

#include "libs/ECS/src/api.hpp"
#include "libs/ECS/src/physics/2d/constants/collision.hpp"
#include "libs/ECS/src/physics/2d/types/collision_2d.hpp"

namespace rtype::sdk::ECS::physics::components {

class EXPORT_ECS_SDK_API Collider2D final {
 public:
  Collider2D() = delete;
  ~Collider2D() = default;

  Collider2D(Rigidbody2D &attachedRigidbody, std::vector<int> collisionLayers,
             Collision2DFunction onCollisionEnter, Collision2DFunction onCollisionExit);

  Collider2D(Rigidbody2D &attachedRigidbody, Collision2DFunction onCollisionEnter,
             Collision2DFunction onCollisionExit);

  Collider2D(const Collider2D &other) = default;
  Collider2D(Collider2D &&other) noexcept = default;

  friend class BoxCollider2D;

 private:
  Collision2DFunction onCollisionEnter_;
  Collision2DFunction onCollisionExit_;
  Rigidbody2D &attachedRigidbody_;
  std::vector<int> collisionLayers_;
};
}  // namespace rtype::sdk::ECS::physics::components
