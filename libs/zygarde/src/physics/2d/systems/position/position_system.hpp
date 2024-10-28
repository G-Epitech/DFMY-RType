/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** position_system.hpp
*/

#pragma once

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"
#include "libs/zygarde/src/core/components/transform/transform.hpp"
#include "libs/zygarde/src/physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "libs/zygarde/src/utils/timer/timer.hpp"

namespace zygarde::physics::systems {
class EXPORT_ZYGARDE_API PositionSystem final
    : public ASystem<components::Rigidbody2D, core::components::Position> {
 public:
  PositionSystem() = default;
  ~PositionSystem() override = default;

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
   * @brief Apply the movement offset to the position
   * @param rigidbody The rigidbody of the entity
   * @param position The position of the entity
   */
  static void ApplyMovementOffset(components::Rigidbody2D* rigidbody,
                                  core::components::Position* position);
};
}  // namespace zygarde::physics::systems
