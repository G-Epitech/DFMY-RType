/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** shark_movement_script.cpp
*/

#include "shark_movement_script.hpp"

#include <random>

rtype::server::game::scripts::SharkMovementScript::SharkMovementScript()
    : speed_{0}, jumpSpeed_{0} {}

void rtype::server::game::scripts::SharkMovementScript::OnEnable(
    const scripting::types::ValuesMap& customScriptValues) {
  speed_ = std::any_cast<float>(customScriptValues.at("speed"));
  jumpSpeed_ = std::any_cast<float>(customScriptValues.at("jumpSpeed"));
  jumpThreshold_ = std::any_cast<float>(customScriptValues.at("jumpThreshold"));
  bottomThreshold_ = std::any_cast<float>(customScriptValues.at("bottomThreshold"));
  jumpChance_ = std::any_cast<float>(customScriptValues.at("jumpChance"));
  stopChance_ = std::any_cast<float>(customScriptValues.at("stopChance"));
}

void rtype::server::game::scripts::SharkMovementScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!position.has_value() || !rb.has_value() || !rb.value() || !position.value()) {
    return;
  }
  if (!position || !rb) {
    return;
  }
  if ((basePosition_.x - (*position)->point.x) >= jumpThreshold_) {
    CheckJump();
  }
  if (jump_) {
    if (((*position)->point.y) < 700) {
      CheckJumpStop();
    }
    if (!jumpStop_ && (*position)->point.y < 200) {
      jumpStop_ = true;
      speed_ /= 1.5;
    }
    if (jumpStop_) {
      (*rb)->SetVelocity({-speed_ * 2, 0});
      return;
    }
    (*rb)->SetVelocity({-jumpSpeed_, -jumpSpeed_});
    return;
  }
  if ((*position)->point.y < bottomThreshold_) {
    (*rb)->SetVelocity({0, 1000});
  } else {
    (*rb)->SetVelocity({-speed_, 0});
  }
}

void rtype::server::game::scripts::SharkMovementScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {}

void rtype::server::game::scripts::SharkMovementScript::SetBasePosition(
    const core::types::Vector3f& basePosition) {
  basePosition_ = basePosition;
}

void rtype::server::game::scripts::SharkMovementScript::CheckJump() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  if (dist(gen) < jumpChance_) {
    jump_ = true;
  }
}

void rtype::server::game::scripts::SharkMovementScript::CheckJumpStop() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  if (dist(gen) < stopChance_) {
    jumpStop_ = true;
  }
}
