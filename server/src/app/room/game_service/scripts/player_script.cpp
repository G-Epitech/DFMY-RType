/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.cpp
*/

#include "player_script.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "helpers/shoot_helper.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripts/enemies/enemy_default_script.hpp"
#include "scripts/helpers/damage_helper.hpp"
#include "zygarde/src/core/components/tags/tags.hpp"

using namespace rtype::server::game::scripts;

PlayerScript::PlayerScript()
    : equippedWeapon_{sdk::game::types::WeaponType::kBasic},
      lastShootTime_{utils::Timer::Nanoseconds::zero()},
      isShooting_{false},
      props_{} {}

void PlayerScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  props_.className = std::any_cast<std::string>(customScriptValues.at("className"));
  health_ = std::any_cast<float>(customScriptValues.at("health"));
  speed_ = std::any_cast<float>(customScriptValues.at("speed"));
  props_.powerCooldown = std::any_cast<float>(customScriptValues.at("powerCooldown"));
  props_.primaryWeapon = std::any_cast<std::string>(customScriptValues.at("primaryWeapon"));
  props_.secondaryWeapon = std::any_cast<std::string>(customScriptValues.at("secondaryWeapon"));
  shootCooldown_ = sdk::game::utils::GetFireRate(sdk::game::stats::WeaponBasic::fireRate);
}

void PlayerScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  lastShootTime_ += context->deltaTime;
  if (isShooting_ && lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    ShootHelper::SpawnBullet(context, kPlayerProjectileOffsetPosition, damageMultiplier_,
                             tools::kArchetypeBasePlayerBullet);
  }
  isShooting_ = false;
  HandleMovement(context);
}

void PlayerScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }
  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kEnemyBulletTag) {
    DamageHelper::HandleDamageTake(&health_, context, entity);
  }
  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kEnemyTag) {
    auto enemyScript = context->registry->GetComponent<scripting::components::ScriptPool>(entity);
    if (enemyScript) {
      auto enemyDefaultScript = (*enemyScript)->GetScript<EnemyDefaultScript>();
      if (enemyDefaultScript) {
        health_ -= enemyDefaultScript->GetHealth();
      }
    }
  }
}

void PlayerScript::HandleMovement(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  if (!movementDirection_) {
    return;
  }
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!rb.has_value() || !rb.value()) {
    return;
  }
  (*rb)->SetVelocity(*movementDirection_ * speed_);
  movementDirection_.reset();
}
