/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** straight_movement.cpp
*/

#include "straight_movement_script.hpp"

using namespace rtype::server::game::scripts;

StraightMovementScript::StraightMovementScript() : speed_{0} {}

void StraightMovementScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  speed_ = std::any_cast<float>(customScriptValues.at("speed"));
}

void StraightMovementScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  if (isWaiting_) {
    currentTime_ += context->deltaTime;
    std::cout << "Waiting" << std::endl;
    if (currentTime_ >= kWaitTime_) {
      isWaiting_ = false;
      currentTime_ = utils::Timer::Nanoseconds::zero();
    }
    return;
  }

  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!position.has_value() || !rb.has_value() || !rb.value() || !position.value()) {
    return;
  }
  if (!position || !rb) {
    return;
  }
  (*rb)->SetVelocity({-speed_, 0});
  if (lastPosition_.x == 0) {
    lastPosition_ = (*position)->point;
    return;
  }
  currentMoveSegment_ += (lastPosition_.x - (*position)->point.x);
  std::cout << "Current move segment: " << currentMoveSegment_ << std::endl;
  lastPosition_ = (*position)->point;
  if (currentMoveSegment_ >= kMoveSegment_) {
    (*rb)->SetVelocity({0, 0});
    currentMoveSegment_ = 0;
    isWaiting_ = true;
  }
}

void StraightMovementScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {}
