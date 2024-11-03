/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnemyDefaultScript.cpp
*/

#include "enemy_default_script.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "constants/tags.hpp"
#include "scripts/helpers/damage_helper.hpp"
#include "scripts/helpers/shoot_helper.hpp"
#include "zygarde/src/core/components/tags/tags.hpp"

using namespace rtype::server::game::scripts;

EnemyDefaultScript::EnemyDefaultScript() : lastShootTime_(utils::Timer::Nanoseconds::zero()) {}

void EnemyDefaultScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  lastShootTime_ += context->deltaTime;
  if (lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    ShootHelper::SpawnBullet(context, kPataProjectileOffsetPosition, damageMultiplier_,
                             bulletArchetype_);
  }
}

void EnemyDefaultScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  auto entity = collision->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag.has_value() || !otherEntityTag.value()) {
    return;
  }

  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kPlayerBulletTag) {
    HandleDamageTake(context, entity);
  }
  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kPlayerTag) {
    context->registry->DestroyEntity(context->me);
  }
}

void EnemyDefaultScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  float fireRate = 0;
  try {
    health_ = std::any_cast<float>(customScriptValues.at("health"));
    bulletArchetype_ = std::any_cast<std::string>(customScriptValues.at("bulletArchetype"));
    scoreIncrease_ = std::any_cast<int>(customScriptValues.at("scoreIncrease"));
    fireRate = std::any_cast<float>(customScriptValues.at("fireRate"));
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  if (fireRate > 0) {
    shootCooldown_ = std::chrono::duration<double>(1.0 / fireRate);
  } else {
    shootCooldown_ = std::chrono::duration<double>::max();
  }
}
