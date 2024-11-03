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

PataScript::PataScript()
    : goingUp_{true},
      horizontalSpeed_{0},
      verticalSpeed_{0},
      basePosition_(0, 0, 0),
      upperLimit_(),
      lowerLimit_(),
      upperLimitOffset_{30.0f},
      lowerLimitOffset_{30.0f},
      lastShootTime_(utils::Timer::Nanoseconds::zero()) {}

void PataScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!position.has_value() || !rb.has_value() || !rb.value() || !position.value()) {
    return;
  }
  lastShootTime_ += context->deltaTime;
  if (lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    ShootHelper::SpawnBullet(context, kPataProjectileOffsetPosition, damageMultiplier_,
                             tools::kArchetypeBaseEnemyBullet);
  }
  if (!position || !rb) {
    return;
  }
  if ((*position)->point.y >= upperLimit_) {
    goingUp_ = false;
  } else if ((*position)->point.y <= lowerLimit_) {
    goingUp_ = true;
  }
  if (goingUp_) {
    (*rb)->SetVelocity({-horizontalSpeed_, verticalSpeed_});
  } else {
    (*rb)->SetVelocity({-horizontalSpeed_, -verticalSpeed_});
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
    DamageHelper::HandleDamageTake(&health_, context, entity);
  }
}

void PataScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  health_ = std::any_cast<float>(customScriptValues.at("health"));
  horizontalSpeed_ = std::any_cast<float>(customScriptValues.at("horizontalSpeed"));
  verticalSpeed_ = std::any_cast<float>(customScriptValues.at("verticalSpeed"));
  upperLimitOffset_ = std::any_cast<float>(customScriptValues.at("upperLimitOffset"));
  lowerLimitOffset_ = std::any_cast<float>(customScriptValues.at("lowerLimitOffset"));
  auto fireRate = std::any_cast<float>(customScriptValues.at("fireRate"));

  if (fireRate > 0) {
    shootCooldown_ = std::chrono::duration<double>(1.0 / fireRate);
  } else {
    shootCooldown_ = std::chrono::duration<double>::max();
  }
}

void PataScript::SetBasePosition(const core::types::Vector3f& basePosition) {
  basePosition_ = basePosition;
  upperLimit_ = basePosition_.y + upperLimitOffset_;
  lowerLimit_ = basePosition_.y - lowerLimitOffset_;
}
