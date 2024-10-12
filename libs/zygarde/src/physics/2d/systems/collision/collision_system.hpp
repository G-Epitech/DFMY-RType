/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.hpp
*/

#pragma once

#include "api.hpp"
#include "core/components/transform/transform.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "physics/2d/types/collision_2d.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::physics::systems {
class EXPORT_ZYGARDE_API CollisionSystem final
    : public ASystem<components::Rigidbody2D, core::components::Transform,
                     components::BoxCollider2D> {
 public:
  explicit CollisionSystem(const utils::Timer::Nanoseconds &deltaTime);
  ~CollisionSystem() override = default;

  void Run(std::shared_ptr<Registry> r,
           tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
           tools::sparse_array<core::components::Transform>::ptr transforms,
           tools::sparse_array<components::BoxCollider2D>::ptr colliders) override;

 private:
  struct ComponentsPack {
    components::Rigidbody2D *rigidbody;
    core::components::Transform *transform;
    components::BoxCollider2D *boxCollider;
  };

 private:
  [[nodiscard]] static bool IndexHasRequiredComponents(
      size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
      const tools::sparse_array<core::components::Transform>::ptr &transforms,
      const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept;

  [[nodiscard]] static ComponentsPack GetComponentsPackAtIndex(
      size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
      const tools::sparse_array<core::components::Transform>::ptr &transforms,
      const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept;

  [[nodiscard]] static bool HaveCommonCollisionLayers(
      components::BoxCollider2D &collider1, components::BoxCollider2D &collider2) noexcept;

  [[nodiscard]] static bool AreColliding(components::BoxCollider2D &collider1,
                                         core::components::Transform &transform1,
                                         components::BoxCollider2D &collider2,
                                         core::components::Transform &transform2) noexcept;

  static void ProcessCollision(ComponentsPack &pack1, ComponentsPack &pack2) noexcept;

  static types::Collision2D BuildCollision2D(ComponentsPack &pack1, ComponentsPack &pack2) noexcept;

  static types::BoundingBox2D GetBoundingBox(components::BoxCollider2D &collider,
                                             core::components::Transform &transform) noexcept;

 private:
  const utils::Timer::Nanoseconds &deltaTime_;
};
}  // namespace zygarde::physics::systems
