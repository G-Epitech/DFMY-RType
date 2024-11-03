/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** zigzag_movement_script.hpp
*/

#pragma once

#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class ZigZagMovementScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  ZigZagMovementScript();
  ~ZigZagMovementScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  void SetBasePosition(const zygarde::core::types::Vector3f& basePosition);

 private:
  bool goingUp_;
  float verticalSpeed_;
  float horizontalSpeed_;
  zygarde::core::types::Vector3f basePosition_;
  float upperLimit_;
  float lowerLimit_;
  float upperLimitOffset_;
  float lowerLimitOffset_;
};
}  // namespace rtype::server::game::scripts
