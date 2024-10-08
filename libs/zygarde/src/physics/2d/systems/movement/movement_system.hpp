/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.hpp
*/

#pragma once

#include <chrono>

#include "core/components/transform/transform.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "system_abstract.hpp"

namespace zygarde::physics::systems {

class MovementSystem final : public ASystem<std::shared_ptr<components::Rigidbody2D>,
                                            std::shared_ptr<core::components::Transform>> {
 public:
  explicit MovementSystem(const std::chrono::duration<float, std::milli> &deltaTime);
  ~MovementSystem() override = default;

  /**
   * @brief Run the system
   * @param r The registry
   * @param components The components
   */
  void Run(std::shared_ptr<Registry> r,
           tools::sparse_array<std::shared_ptr<components::Rigidbody2D>> &rigidbodies,
           tools::sparse_array<std::shared_ptr<core::components::Transform>> &transforms) override;

 private:
  void ComputeMovementOffset(const std::shared_ptr<components::Rigidbody2D> &rigidbody);

  [[nodiscard]] float GetDeltaTimeInSeconds() const noexcept;

  void UpdateTransformPosition(const std::shared_ptr<core::components::Transform> &transform) const;

 private:
  const std::chrono::duration<float, std::milli> &deltaTime_;
  core::types::Vector2f movementOffset_ = core::types::Vector2f::zero();
};
}  // namespace zygarde::physics::systems
