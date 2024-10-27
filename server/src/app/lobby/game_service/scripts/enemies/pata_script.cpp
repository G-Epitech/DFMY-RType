/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PataScript.cpp
*/

#include "pata_script.hpp"

#include "app/lobby/game_service/factories/projectile_factory.hpp"
#include "constants/tags.hpp"
#include "types/game_entities.hpp"

using namespace rtype::server::game::scripts;

PataScript::PataScript()
    : health_{50},
      goingUp_{true},
      basePosition_(0, 0, 0),
      upperLimit_(basePosition_.y + 30.0f),
      lowerLimit_(basePosition_.y - 30.0f),
      lastShootTime_(utils::Timer::Nanoseconds::zero()) {}

void PataScript::FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  if (health_ <= 0) {
    context->registry->DestroyEntity(context->me);
  }

  auto position = context->registry->GetComponent<core::components::Position>(context->me);
  auto rb = context->registry->GetComponent<physics::components::Rigidbody2D>(context->me);
  lastShootTime_ += context->deltaTime;
  if (lastShootTime_ >= std::chrono::seconds(1)) {
    lastShootTime_ = utils::Timer::Nanoseconds::zero();
    auto bullet = ProjectileFactory::CreateProjectile(context->registry, position->point, {32, 15},
                                                      sdk::game::types::GameEntityType::kEnemy);
  }
  if (!position || !rb) {
    return;
  }
  if (position->point.y >= upperLimit_) {
    goingUp_ = false;
  } else if (position->point.y <= lowerLimit_) {
    goingUp_ = true;
  }
  float verticalSpeed = 20.0f;
  if (goingUp_) {
    rb->SetVelocity({-100.0f, verticalSpeed});
  } else {
    rb->SetVelocity({-100.0f, -verticalSpeed});
  }
}

void PataScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  auto entity = collision->otherEntity;
  auto otherEntityTag = context->registry->GetComponent<core::components::Tags>(entity);
  if (!otherEntityTag) {
    return;
  }

  if (*otherEntityTag == rtype::sdk::game::constants::kPlayerBulletTag) {
    health_ -= 10;
  }
}
