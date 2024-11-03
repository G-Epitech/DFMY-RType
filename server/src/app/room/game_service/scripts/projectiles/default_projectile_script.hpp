/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base_projectile.hpp
*/

#pragma once

#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "scripting/components/script/script.hpp"
#include "types/weapons.hpp"

namespace rtype::server::game::scripts {
class DefaultProjectileScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  DefaultProjectileScript() = default;
  ~DefaultProjectileScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  inline void SetDamage(float damage) { damage_ = damage; }

  [[nodiscard]] inline float GetDamage() const { return damage_; }

 private:
  float damage_ = 10;
};
}  // namespace rtype::server::game::scripts
