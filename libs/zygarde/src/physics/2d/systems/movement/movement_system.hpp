/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.hpp
*/

#pragma once

#include <chrono>

#include "api.hpp"
#include "core/components/position/position.hpp"
#include "core/components/transform/transform.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::physics::systems {

class EXPORT_ZYGARDE_API MovementSystem final
    : public ASystem<components::Rigidbody2D, core::components::Position> {
 public:
  /**
   * @brief Construct a new Movement System object
   * @param delta_time Delta time (provided by the game loop)
   */
  explicit MovementSystem(const utils::Timer::Nanoseconds &delta_time);
  ~MovementSystem() override = default;

  /**
   * @brief Run the system
   * @param r The registry to use
   * @param rigidbodies The rigidbodies to use
   * @param positions The positions to use
   */
  void Run(std::shared_ptr<Registry> r,
           tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
           tools::sparse_array<core::components::Position>::ptr positions) override;

 private:
  /**
   * @brief Compute the position offset
   * @param rigidbody The rigidbody of the entity
   */
  void ComputePositionOffset(components::Rigidbody2D *rigidbody);

  /**
   * @brief Update the position
   * @param position The position of the entity
   */
  void UpdatePosition(core::components::Position *position) const;

 private:
  /// @brief Delta time
  const utils::Timer::Nanoseconds &deltaTime_;
  /// @brief Movement offset
  core::types::Vector2f movementOffset_ = core::types::Vector2f::zero();
};
}  // namespace zygarde::physics::systems
