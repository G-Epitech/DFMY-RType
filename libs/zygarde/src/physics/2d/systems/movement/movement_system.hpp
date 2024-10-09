/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.hpp
*/

#pragma once

#include <chrono>

#include "api.hpp"
#include "core/components/transform/transform.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::physics::systems {

class EXPORT_ZYGARDE_API MovementSystem final
    : public ASystem<std::shared_ptr<components::Rigidbody2D>,
                     std::shared_ptr<core::components::Transform>> {
 public:
  /**
   * @brief Construct a new Movement System object
   * @param deltaTime Delta time (provided by the game loop)
   */
  explicit MovementSystem(const utils::Timer::Nanoseconds &deltaTime);
  ~MovementSystem() override = default;

  /**
   * @brief Run the system
   * @param r The registry to use
   * @param rigidbodies The rigidbodies to use
   * @param transforms The transforms to use
   */
  void Run(std::shared_ptr<Registry> r,
           tools::sparse_array<std::shared_ptr<components::Rigidbody2D>> &rigidbodies,
           tools::sparse_array<std::shared_ptr<core::components::Transform>> &transforms) override;

 private:
  /**
   * @brief Compute the position offset
   * @param rigidbody The rigidbody of the entity
   */
  void ComputePositionOffset(const std::shared_ptr<components::Rigidbody2D> &rigidbody);

  /**
   * @brief Update the transform position
   * @param transform The transform of the entity
   */
  void UpdateTransformPosition(const std::shared_ptr<core::components::Transform> &transform) const;

 private:
  /// @brief Delta time
  const utils::Timer::Nanoseconds &deltaTime_;
  /// @brief Movement offset
  core::types::Vector2f movementOffset_ = core::types::Vector2f::zero();
};
}  // namespace zygarde::physics::systems
