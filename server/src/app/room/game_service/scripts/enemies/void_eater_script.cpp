/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** void_eater_script.cpp
*/

#include "void_eater_script.hpp"

#include "constants/tags.hpp"
#include "core/components/tags/tags.hpp"
#include "scripts/helpers/shoot_helper.hpp"

using namespace rtype::server::game::scripts;

VoidEaterScript::VoidEaterScript()
    : lastShootTimes_{std::vector<zygarde::utils::Timer::Nanoseconds>(
          kVoidEaterShootOffset.size(), utils::Timer::Nanoseconds::zero())} {}

void VoidEaterScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  for (size_t i = 0; i < kVoidEaterShootOffset.size(); i++) {
    lastShootTimes_[i] += context->deltaTime;
    if (lastShootTimes_[i] >= shootCooldown_) {
      lastShootTimes_[i] = utils::Timer::Nanoseconds::zero();
      ShootHelper::SpawnBullet(context, kVoidEaterShootOffset[i], damageMultiplier_,
                               bulletArchetype_);
    }
  }
}

void VoidEaterScript::OnCollisionEnter(
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
}

void VoidEaterScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
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
