/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** straight_movement.hpp
*/

#pragma once

#include "base_movement_script.hpp"

namespace rtype::server::game::scripts {
class StraightMovementScript : public BaseMovementScript {
 public:
  StraightMovementScript();
  ~StraightMovementScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

 private:
  static constexpr float kMoveSegment_ = 700;
  static constexpr utils::Timer::Nanoseconds kWaitTime_ = std::chrono::seconds(3);

 private:
  float speed_;
  float currentMoveSegment_{0};
  core::types::Vector3f lastPosition_ = basePosition_;
  utils::Timer::Nanoseconds currentTime_{utils::Timer::Nanoseconds::zero()};
  bool isWaiting_{false};
};
}  // namespace rtype::server::game::scripts
