/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base_projectile.cpp
*/

#include "base_projectile_script.hpp"

using namespace rtype::server::game::scripts;

void rtype::server::game::scripts::BaseProjectileScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {
  const auto posComponent =
      context->registry->GetComponent<core::components::Position>(context->me);
  if (!posComponent.has_value() || !posComponent.value()) {
    return;
  }
  if ((*posComponent)->point.x > 2000 || (*posComponent)->point.x < -200) {
    context->registry->DestroyEntity(context->me);
  }
}

void BaseProjectileScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  context->registry->DestroyEntity(context->me);
}

void BaseProjectileScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {}
