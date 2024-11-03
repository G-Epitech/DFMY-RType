/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** zigzag_movement_script.cpp
*/

#include "zigzag_movement_script.hpp"

using namespace rtype::server::game::scripts;

ZigZagMovementScript::ZigZagMovementScript()
    : goingUp_{true},
      horizontalSpeed_{0},
      verticalSpeed_{0},
      basePosition_(0, 0, 0),
      upperLimit_(),
      lowerLimit_(),
      upperLimitOffset_{30.0f},
      lowerLimitOffset_{30.0f} {}

void ZigZagMovementScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  horizontalSpeed_ = std::any_cast<float>(customScriptValues.at("horizontalSpeed"));
  verticalSpeed_ = std::any_cast<float>(customScriptValues.at("verticalSpeed"));
  upperLimitOffset_ = std::any_cast<float>(customScriptValues.at("upperLimitOffset"));
  lowerLimitOffset_ = std::any_cast<float>(customScriptValues.at("lowerLimitOffset"));
}

void ZigZagMovementScript::SetBasePosition(const core::types::Vector3f& basePosition) {
  basePosition_ = basePosition;
  upperLimit_ = basePosition_.y + upperLimitOffset_;
  lowerLimit_ = basePosition_.y - lowerLimitOffset_;
}

void ZigZagMovementScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {}

void ZigZagMovementScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!position.has_value() || !rb.has_value() || !rb.value() || !position.value()) {
    return;
  }

  if (!position || !rb) {
    return;
  }
  if ((*position)->point.y >= upperLimit_) {
    goingUp_ = false;
  } else if ((*position)->point.y <= lowerLimit_) {
    goingUp_ = true;
  }
  if (goingUp_) {
    (*rb)->SetVelocity({-horizontalSpeed_, verticalSpeed_});
  } else {
    (*rb)->SetVelocity({-horizontalSpeed_, -verticalSpeed_});
  }
}
