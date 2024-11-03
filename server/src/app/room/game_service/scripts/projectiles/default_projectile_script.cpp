/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base_projectile.cpp
*/

#include "default_projectile_script.hpp"

using namespace rtype::server::game::scripts;

void rtype::server::game::scripts::DefaultProjectileScript::FixedUpdate(
    const std::shared_ptr<scripting::types::ScriptingContext>& context) {}

void DefaultProjectileScript::OnCollisionEnter(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const physics::types::Collision2D::ptr& collision) {
  context->registry->DestroyEntity(context->me);
}

void DefaultProjectileScript::OnEnable(const scripting::types::ValuesMap& customScriptValues) {}
