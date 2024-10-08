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
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param collision_layers Collision layers
   * @param on_collision_enter On collision enter function callback
   * @param on_collision_exit On collision exit function callback
   */
  Collider2D(std::shared_ptr<Rigidbody2D> attached_rigidbody, std::vector<int> collision_layers,
             Collision2DFunction on_collision_enter, Collision2DFunction on_collision_exit);

  /**
   * @brief Construct a new Collider2D object
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param on_collision_enter On collision enter function callback
   * @param on_collision_exit On collision exit function callback
   */
  Collider2D(std::shared_ptr<Rigidbody2D> attached_rigidbody,
             Collision2DFunction on_collision_enter, Collision2DFunction on_collision_exit);

  friend class BoxCollider2D;

 private:
  /// @brief On collision enter function callback
  Collision2DFunction onCollisionEnter_;
  /// @brief On collision exit function callback
  Collision2DFunction onCollisionExit_;
  /// @brief Pointer to the attached Rigidbody2D object
  std::shared_ptr<Rigidbody2D> attachedRigidbody_;
  /// @brief Collision layers
  std::vector<int> collisionLayers_;
};
}  // namespace zygarde::physics::components
