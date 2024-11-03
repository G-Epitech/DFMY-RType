/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyDefaultScript.hpp
*/

#pragma once

#include "scripts/base/enemy_base_script.hpp"
#include "zygarde/src/physics/2d/components/components.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game::scripts {
static constexpr zygarde::core::types::Vector3f kPataProjectileOffsetPosition{-40, 30, 0};
}

namespace rtype::server::game::scripts {
class EnemyDefaultScript : public EnemyBaseScript {
 public:
  EnemyDefaultScript();
  ~EnemyDefaultScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

 private:
  zygarde::utils::Timer::Nanoseconds lastShootTime_;
  std::string bulletArchetype_;
};
}  // namespace rtype::server::game::scripts
