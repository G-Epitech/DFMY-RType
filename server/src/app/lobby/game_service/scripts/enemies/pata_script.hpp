/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PataScript.hpp
*/

#pragma once

#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game::scripts {
class PataScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  PataScript();
  ~PataScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

 private:
  static void SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context);

 private:
  float health_;
  bool goingUp_;
  zygarde::core::types::Vector3f basePosition_;
  float upperLimit_;
  float lowerLimit_;
  zygarde::utils::Timer::Nanoseconds lastShootTime_;
};
}  // namespace rtype::server::game::scripts
