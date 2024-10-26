/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.hpp
*/

#pragma once

#include "app/lobby/game_service/factories/projectile_factory.hpp"
#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "types/weapons.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class PlayerScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  PlayerScript();
  ~PlayerScript() override = default;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  inline void Shoot() { isShooting_ = true; }

 private:
  float health_;
  sdk::game::types::WeaponType equippedWeapon_;
  std::chrono::nanoseconds shootCooldown_;
  std::chrono::nanoseconds lastShootTime_;
  bool isShooting_;
};
}  // namespace rtype::server::game::scripts
