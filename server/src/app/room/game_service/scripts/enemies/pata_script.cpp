/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PataScript.cpp
*/

#include "pata_script.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "constants/tags.hpp"
#include "scripts/helpers/damage_helper.hpp"
#include "scripts/helpers/shoot_helper.hpp"
#include "zygarde/src/core/components/tags/tags.hpp"

using namespace rtype::server::game::scripts;

PataScript::PataScript() : lastShootTime_(utils::Timer::Nanoseconds::zero()) {}

void PataScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  lastShootTime_ += context->deltaTime;
  if (lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    ShootHelper::SpawnBullet(context, kPataProjectileOffsetPosition, damageMultiplier_,
                             tools::kArchetypeBaseEnemyBullet);
  }
}

void PataScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  auto entity = collision->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag.has_value() || !otherEntityTag.value()) {
    return;
  }

  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kPlayerBulletTag) {
    std::cout << "PataScript::OnCollisionEnter" << std::endl;
    HandleDamageTake(context, entity);
  }
}

void PataScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  health_ = std::any_cast<float>(customScriptValues.at("health"));
  auto fireRate = std::any_cast<float>(customScriptValues.at("fireRate"));

  if (fireRate > 0) {
    shootCooldown_ = std::chrono::duration<double>(1.0 / fireRate);
  } else {
    shootCooldown_ = std::chrono::duration<double>::max();
  }
}
