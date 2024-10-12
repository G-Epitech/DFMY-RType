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
#include "utils/timer/timer.hpp"

namespace zygarde::physics::systems {
class EXPORT_ZYGARDE_API CollisionSystem final
    : public ASystem<components::Rigidbody2D, core::components::Position,
                     components::BoxCollider2D> {
 public:
  CollisionSystem() = default;
  ~CollisionSystem() override = default;

  void Run(std::shared_ptr<Registry> r,
           tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
           tools::sparse_array<core::components::Position>::ptr positions,
           tools::sparse_array<components::BoxCollider2D>::ptr colliders) override;

 private:
  struct ComponentsPack {
    components::Rigidbody2D *rigidbody;
    core::components::Position *position;
    components::BoxCollider2D *boxCollider;
  };

 private:
  [[nodiscard]] static bool IndexHasRequiredComponents(
      size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
      const tools::sparse_array<core::components::Position>::ptr &positions,
      const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept;

  [[nodiscard]] static ComponentsPack GetComponentsPackAtIndex(
      size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
      const tools::sparse_array<core::components::Position>::ptr &positions,
      const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept;

  [[nodiscard]] static bool HaveCommonCollisionLayers(
      const components::BoxCollider2D &collider1,
      const components::BoxCollider2D &collider2) noexcept;

  [[nodiscard]] static bool AreColliding(const physics::components::BoxCollider2D &collider1,
                                         const core::components::Position &position1,
                                         const physics::components::BoxCollider2D &collider2,
                                         const core::components::Position &position2) noexcept;

  static void ProcessCollision(const ComponentsPack &pack1, const ComponentsPack &pack2) noexcept;

  [[nodiscard]] static types::Collision2D BuildCollision2D(const ComponentsPack &pack1,
                                                           const ComponentsPack &pack2) noexcept;
};
}  // namespace zygarde::physics::systems
