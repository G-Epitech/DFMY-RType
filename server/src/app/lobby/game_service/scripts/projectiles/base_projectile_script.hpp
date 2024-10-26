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
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class BaseProjectileScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  BaseProjectileScript() = default;
  ~BaseProjectileScript() override = default;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;
};
}  // namespace rtype::server::game::scripts
