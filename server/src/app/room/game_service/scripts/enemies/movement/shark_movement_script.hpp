/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** shark_movement_script.hpp
*/

#pragma once

#include "base_movement_script.hpp"

namespace rtype::server::game::scripts {
class SharkMovementScript : public BaseMovementScript {
 public:
  SharkMovementScript();
  ~SharkMovementScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  void SetBasePosition(const zygarde::core::types::Vector3f& basePosition) override;

 private:
  void CheckJump();
  void CheckJumpStop();

 private:
  float speed_;
  float jumpSpeed_;
  float jumpThreshold_{0};
  float bottomThreshold_{0};
  float jumpChance_{0};
  float stopChance_{0};
  bool jump_{false};
  bool jumpStop_{false};
};
}  // namespace rtype::server::game::scripts
