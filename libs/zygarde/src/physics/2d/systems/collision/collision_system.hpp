/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.hpp
*/

#pragma once

#include "api.hpp"
#include "core/components/position/position.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "physics/2d/types/bounding_box/builder.hpp"
#include "physics/2d/types/collision_2d.hpp"
#include "system_abstract.hpp"

namespace zygarde::physics::systems {
class EXPORT_ZYGARDE_API CollisionSystem final
    : public ASystem<components::Rigidbody2D, core::components::Position,
                     components::BoxCollider2D> {
 public:
  CollisionSystem() = default;
  ~CollisionSystem() override = default;

  /**
   * @brief Run the collision system
   * @param r Registry
   * @param components Components to run the system on
   */
  void Run(std::shared_ptr<Registry> r,
           zipper<components::Rigidbody2D, core::components::Position, components::BoxCollider2D>
               components) override;

 private:
  /// @brief Struct to hold entity components
  struct EntityComponents {
    /// @brief Rigidbody2D component
    components::Rigidbody2D *rigidbody;
    /// @brief Position component
    core::components::Position *position;
    /// @brief BoxCollider2D component
    components::BoxCollider2D *boxCollider;
    /// @brief Entity
    Entity entity;
  };

 private:
  /**
   * @brief Check if two colliders have matching collision layers
   * @param self_collider Collider to check
   * @param other_collider Other collider to check
   * @return true if they have matching collision layers
   */
  [[nodiscard]] static bool HasMatchingCollisionLayers(
      const components::BoxCollider2D &self_collider,
      const components::BoxCollider2D &other_collider) noexcept;

  /**
   * @brief Get the simulated position of a Rigidbody2D object (position + movement offset)
   * @param rigidbody Rigidbody2D object containing the movement offset
   * @param position Position object to get the position from
   * @return Simulated position
   */
  [[nodiscard]] static core::components::Position GetSimulatedPosition(
      components::Rigidbody2D *rigidbody, core::components::Position *position) noexcept;

  /**
   * @brief Check if two entities are colliding
   * @param self_pack Components of the first entity
   * @param other_pack Components of the second entity
   * @return true if they are colliding
   */
  [[nodiscard]] static bool CheckCollision(const EntityComponents &self_pack,
                                           const EntityComponents &other_pack) noexcept;

  /**
   * @brief Check if two bounding boxes are overlapping
   * @param self_bounding_box First bounding box
   * @param other_bounding_box Second bounding box
   * @return true if they are overlapping
   */
  [[nodiscard]] static bool CheckBoundingBoxOverlap(
      const physics::types::BoundingBox2D &self_bounding_box,
      const physics::types::BoundingBox2D &other_bounding_box) noexcept;

  /**
   * @brief Resolve the collision between two entities
   * @param self_pack First entity components
   * @param other_pack Second entity components
   */
  static void ResolveCollision(const EntityComponents &self_pack,
                               const EntityComponents &other_pack) noexcept;

  /**
   * @brief Build a Collision2D object from two entity components
   * @param self_pack First entity components
   * @param other_pack Second entity components
   * @return Collision2D object
   */
  [[nodiscard]] static types::Collision2D BuildCollision2D(
      const EntityComponents &self_pack, const EntityComponents &other_pack) noexcept;
};
}  // namespace zygarde::physics::systems
