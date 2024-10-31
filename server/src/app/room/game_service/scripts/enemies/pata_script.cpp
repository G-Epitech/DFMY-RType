/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PataScript.cpp
*/

#include "pata_script.hpp"

#include "app/room/game_service/archetype_keys.hpp"
#include "constants/tags.hpp"
#include "zygarde/src/core/components/tags/tags.hpp"

using namespace rtype::server::game::scripts;

PataScript::PataScript()
    : health_{50},
      goingUp_{true},
      basePosition_(0, 0, 0),
      upperLimit_(basePosition_.y + 30.0f),
      lowerLimit_(basePosition_.y - 30.0f),
      lastShootTime_(utils::Timer::Nanoseconds::zero()) {}

void PataScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  if (!position.has_value() || !rb.has_value() || !rb.value() || !position.value()) {
    return;
  }
  lastShootTime_ += context->deltaTime;
  if (lastShootTime_ >= std::chrono::seconds(1)) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    SpawnBullet(context);
  }
  if (!position || !rb) {
    return;
  }
  if ((*position)->point.y >= upperLimit_) {
    goingUp_ = false;
  } else if ((*position)->point.y <= lowerLimit_) {
    goingUp_ = true;
  }
  float verticalSpeed = 20.0f;
  if (goingUp_) {
    (*rb)->SetVelocity({-100.0f, verticalSpeed});
  } else {
    (*rb)->SetVelocity({-100.0f, -verticalSpeed});
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
    health_ -= 10;
    std::cout << "Pata health: " << health_ << std::endl;
  }
  if (health_ <= 0) {
    context->registry->DestroyEntity(context->me);
    return;
  }
}

void PataScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {}

void PataScript::SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  if (!position.has_value() || !position.value()) {
    return;
  }
  const core::types::Vector3f projectilePos((*position)->point.x - 86, (*position)->point.y - 20,
                                            (*position)->point.z);
  zygarde::core::archetypes::ArchetypeManager::InvokationParams params;
  params.archetypeName = tools::kArchetypeBaseEnemyBullet;
  params.registryAttachCallback = [projectilePos](const std::shared_ptr<zygarde::Registry>& registry,
                                                  const zygarde::Entity& entity) -> void {
    auto positionComponent = registry->GetComponent<core::components::Position>(entity);
    if (positionComponent.has_value() && positionComponent.value()) {
      (*positionComponent)->point = projectilePos;
    }
  };
  context->archetypeManager->ScheduleInvocation(params);
}
