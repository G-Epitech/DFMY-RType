/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** void_eater_script.hpp
*/

#pragma once

#include "scripts/base/enemy_base_script.hpp"
#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game::scripts {
static inline const std::vector<core::types::Vector3f> kVoidEaterShootOffset = {
    core::types::Vector3f{-50, 0, 0},   core::types::Vector3f{0, 80, 0},
    core::types::Vector3f{50, 160, 0},  core::types::Vector3f{100, 240, 0},
    core::types::Vector3f{200, 320, 0}, core::types::Vector3f{300, 400, 0},
};
}

namespace rtype::server::game::scripts {
class VoidEaterScript : public EnemyBaseScript {
 public:
  VoidEaterScript();
  ~VoidEaterScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

 private:
  std::vector<zygarde::utils::Timer::Nanoseconds> lastShootTimes_;
  std::string bulletArchetype_;
};
}  // namespace rtype::server::game::scripts
