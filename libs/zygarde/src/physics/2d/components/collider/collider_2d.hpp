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

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/physics/2d/constants/collision.hpp"
#include "libs/zygarde/src/physics/2d/types/collision_2d.hpp"

namespace zygarde::physics::components {

class EXPORT_ZYGARDE_API Collider2D final {
 public:
  Collider2D() = delete;

 private:
  ~Collider2D() = default;

  /**
   * @brief Construct a new Collider2D object
   * @param attachedRigidbody Reference to the attached Rigidbody2D object
   * @param collisionLayers Collision layers
   * @param onCollisionEnter On collision enter function callback
   * @param onCollisionExit On collision exit function callback
   */
  Collider2D(Rigidbody2D &attachedRigidbody, std::vector<int> collisionLayers,
             Collision2DFunction onCollisionEnter, Collision2DFunction onCollisionExit);

  /**
   * @brief Construct a new Collider2D object
   * @param attachedRigidbody Reference to the attached Rigidbody2D object
   * @param onCollisionEnter On collision enter function callback
   * @param onCollisionExit On collision exit function callback
   */
  Collider2D(Rigidbody2D &attachedRigidbody, Collision2DFunction onCollisionEnter,
             Collision2DFunction onCollisionExit);

  friend class BoxCollider2D;

 private:
  /// @brief On collision enter function callback
  Collision2DFunction onCollisionEnter_;
  /// @brief On collision exit function callback
  Collision2DFunction onCollisionExit_;
  /// @brief Reference to the attached Rigidbody2D object
  Rigidbody2D &attachedRigidbody_;
  /// @brief Collision layers
  std::vector<int> collisionLayers_;
};
}  // namespace zygarde::physics::components
