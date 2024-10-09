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
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::physics::systems {
class EXPORT_ZYGARDE_API CollisionSystem final
    : public ASystem<components::Rigidbody2D *, core::components::Transform *,
                     components::BoxCollider2D *> {
 public:
  explicit CollisionSystem(const utils::Timer::Nanoseconds &deltaTime);
  ~CollisionSystem() override = default;

  void Run(std::shared_ptr<Registry> r, tools::sparse_array<components::Rigidbody2D *> &rigidbodies,
           tools::sparse_array<core::components::Transform *> &transforms,
           tools::sparse_array<components::BoxCollider2D *> &colliders) override;

 private:
  const utils::Timer::Nanoseconds &deltaTime_;
};
}  // namespace zygarde::physics::systems
