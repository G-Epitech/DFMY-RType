/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.cpp
*/

#include "player_script.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "zygarde/src/core/components/tags/tags.hpp"

using namespace rtype::server::game::scripts;

PlayerScript::PlayerScript()
    : equippedWeapon_{sdk::game::types::WeaponType::kBasic},
      shootCooldown_{sdk::game::utils::GetFireRate(sdk::game::stats::WeaponBasic::fireRate)},
      lastShootTime_{utils::Timer::Nanoseconds::zero()},
      isShooting_{false} {}

void PlayerScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {
  props_.className = std::any_cast<std::string>(customScriptValues.at("className"));
  props_.health = std::any_cast<float>(customScriptValues.at("health"));
  props_.speed = std::any_cast<float>(customScriptValues.at("speed"));
  props_.powerCooldown = std::any_cast<float>(customScriptValues.at("powerCooldown"));
  props_.primaryWeapon = std::any_cast<std::string>(customScriptValues.at("primaryWeapon"));
  props_.secondaryWeapon = std::any_cast<std::string>(customScriptValues.at("secondaryWeapon"));
}

void PlayerScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  lastShootTime_ += context->deltaTime;
  if (isShooting_ && lastShootTime_ >= shootCooldown_) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    SpawnBullet(context);
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
  if ((*otherEntityTag.value()) & rtype::sdk::game::constants::kEnemyBulletTag) {
    props_.health -= 10;
  }
  if (props_.health <= 0) {
    context->registry->DestroyEntity(context->me);
  }
}

void PlayerScript::SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  if (!position.has_value() || !position.value()) {
    return;
  }
  const core::types::Vector3f projectilePos((*position)->point.x + 86, (*position)->point.y + 20,
                                            (*position)->point.z);
  zygarde::core::archetypes::ArchetypeManager::ScheduleInvocationParams params;
  params.archetypeName = tools::kArchetypeBasePlayerBullet;
  params.registryAttachCallback = [projectilePos](const std::shared_ptr<zygarde::Registry>& registry,
                                                  const zygarde::Entity& entity) -> void {
    auto positionComponent = registry->GetComponent<core::components::Position>(entity);
    if (positionComponent.has_value() && positionComponent.value()) {
      (*positionComponent)->point = projectilePos;
    }
  };
  context->archetypeManager->ScheduleInvocation(params);
}
