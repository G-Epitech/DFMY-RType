/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PataScript.hpp
*/

#pragma once

#include "scripts/base/enemy_base_script.hpp"
#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game::scripts {
class PataScript : public EnemyBaseScript {
 public:
  PataScript();
  ~PataScript() override = default;

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
  zygarde::utils::Timer::Nanoseconds lastShootTime_;

 private:
  static constexpr zygarde::core::types::Vector3f kProjectileOffsetPosition_{-40, 10, 0};
};
}  // namespace rtype::server::game::scripts
