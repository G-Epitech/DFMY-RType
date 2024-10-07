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

#include "libs/ECS/src/physics/2d/constants/collision.hpp"
#include "libs/ECS/src/physics/2d/types/collision_2d.hpp"

namespace rtype::sdk::ECS::physics::components {

class Collider2D final {
 public:
  Collider2D() = delete;
  ~Collider2D() = default;

  Collider2D(Rigidbody2D &attachedRigidbody, std::vector<int> collisionLayers,
             CollisionFunction onCollisionEnter, CollisionFunction onCollisionExit);

  Collider2D(Rigidbody2D &attachedRigidbody, CollisionFunction onCollisionEnter,
             CollisionFunction onCollisionExit);

  Collider2D(const Collider2D &other) = default;
  Collider2D &operator=(const Collider2D &other) = default;
  Collider2D(Collider2D &&other) noexcept = default;
  Collider2D &operator=(Collider2D &&other) noexcept = default;

  friend class BoxCollider2D;

 public:
  CollisionFunction onCollisionEnter;
  CollisionFunction onCollisionExit;

 private:
  Rigidbody2D &attachedRigidbody_;
  std::vector<int> collisionLayers_;
};
}  // namespace rtype::sdk::ECS::physics::components
