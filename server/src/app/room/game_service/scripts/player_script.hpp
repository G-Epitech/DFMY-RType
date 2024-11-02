/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.hpp
*/

#pragma once

#include "base/player_base_script.hpp"
#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "types/weapons.hpp"
#include "zygarde/src/core/types/vector/vector_2f.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
static constexpr core::types::Vector3f kPlayerProjectileOffsetPosition{80.0f, 20.0f, 0.0f};
}

namespace rtype::server::game::scripts {
class PlayerScript : public PlayerBaseScript {
 public:
  struct PlayerProps {
    std::string className;
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

  inline void SetMovementDirection(const core::types::Vector2f& direction) {
    movementDirection_ = direction;
  }

 private:
  void HandleMovement(const std::shared_ptr<scripting::types::ScriptingContext>& context);

 private:
  PlayerProps props_;
  sdk::game::types::WeaponType equippedWeapon_;
  std::chrono::nanoseconds lastShootTime_;
  bool isShooting_;
  std::optional<core::types::Vector2f> movementDirection_;
};
}  // namespace rtype::server::game::scripts
