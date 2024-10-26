/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.cpp
*/

#include "player_script.hpp"

using namespace rtype::server::game::scripts;

PlayerScript::PlayerScript()
    : health_{100},
      equippedWeapon_{sdk::game::types::WeaponType::kBasic},
      shootCooldown_{sdk::game::utils::GetFireRate(sdk::game::stats::WeaponBasic::fireRate)},
      lastShootTime_{utils::Timer::Nanoseconds::zero()},
      isShooting_{false} {}

void PlayerScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  lastShootTime_ += context->deltaTime;
  if (isShooting_ && lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    isShooting_ = false;
    auto position = context->registry->GetComponent<core::components::Position>(context->me);

    const core::types::Vector3f projectilePos(position->point.x + 86, position->point.y + 20,
                                              position->point.z);
    ProjectileFactory::CreateProjectile(context->registry, projectilePos, {32, 15},
                                        sdk::game::types::GameEntityType::kPlayer);
    return;
  }
  isShooting_ = false;
}

void PlayerScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  auto entity = collision.get()->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }
  if (*otherEntityTag == rtype::sdk::game::constants::kEnemyBulletTag) {
    health_ -= 10;
  }
  if (health_ <= 0) {
    context->registry->DestroyEntity(context->me);
  }
}
