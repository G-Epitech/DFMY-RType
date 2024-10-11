/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.hpp
*/

#pragma once

#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/physics/2d/types/collision_2d.hpp"

namespace zygarde::physics::systems {
class CollisionSystem;
}

namespace zygarde::physics::components {

class EXPORT_ZYGARDE_API Collider2D final {
 public:
  using ptr = std::shared_ptr<Collider2D>;

 public:
  Collider2D() = delete;

 private:
  ~Collider2D() = default;

  /**
   * @brief Construct a new Collider2D object
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   * @param collision_layers Collision layers
   */
  Collider2D(Rigidbody2D::ptr attached_rigidbody, std::vector<int> collision_layers,
             const core::types::Vector2f &position);

  /**
   * @brief Construct a new Collider2D object
   * @param attached_rigidbody Pointer to the attached Rigidbody2D object
   */
  explicit Collider2D(Rigidbody2D::ptr attached_rigidbody, const core::types::Vector2f &position);

  inline void SetOnCollisionEnter(Collision2DFunction on_collision_enter) {
    onCollisionEnter_ = std::move(on_collision_enter);
  }

  inline void SetOnCollisionExit(Collision2DFunction on_collision_exit) {
    onCollisionExit_ = std::move(on_collision_exit);
  }

  friend class BoxCollider2D;

 private:
  /// @brief On collision enter function callback
  std::optional<Collision2DFunction> onCollisionEnter_;
  /// @brief On collision exit function callback
  std::optional<Collision2DFunction> onCollisionExit_;
  /// @brief Pointer to the attached Rigidbody2D object
  Rigidbody2D::ptr attachedRigidbody_;
  /// @brief Collision layers
  std::vector<int> collisionLayers_ = std::vector<int>{0};
  /// @brief Reference to the position of the entity
  const core::types::Vector2f &position_;
};
}  // namespace zygarde::physics::components
