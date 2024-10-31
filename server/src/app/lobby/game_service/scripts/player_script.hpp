/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.hpp
*/

#pragma once

#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "types/weapons.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class PlayerScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  struct PlayerProps {
    std::string className;
    float health;
    float speed;
    float powerCooldown;
    std::string primaryWeapon;
    std::string secondaryWeapon;
  };

 public:
  PlayerScript();
  ~PlayerScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  inline void Shoot() { isShooting_ = true; }

  inline void SetPlayerProps(const PlayerProps& props) { props_ = props; }

 private:
  PlayerProps props_;
  sdk::game::types::WeaponType equippedWeapon_;
  std::chrono::nanoseconds shootCooldown_;
  std::chrono::nanoseconds lastShootTime_;
  bool isShooting_;
};
}  // namespace rtype::server::game::scripts
