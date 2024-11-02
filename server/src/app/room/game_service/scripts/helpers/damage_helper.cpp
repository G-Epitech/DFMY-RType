/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** damage_take_script.cpp
*/

#include "damage_helper.hpp"

#include "scripting/components/pool/script_pool.hpp"
#include "scripts/projectiles/default_projectile_script.hpp"

void rtype::server::game::scripts::DamageHelper::HandleDamageTake(
    float *health, const std::shared_ptr<scripting::types::ScriptingContext> &context,
    const Entity &other_entity) {
  auto scriptPool =
      context->registry->GetComponent<scripting::components::ScriptPool>(other_entity);

  if (!scriptPool.has_value() || !scriptPool.value()) {
    return;
  }
  auto otherScript = scriptPool.value()->GetScript<scripts::DefaultProjectileScript>();
  (*health) -= otherScript->GetDamage();

  if ((*health) <= 0) {
    context->registry->DestroyEntity(context->me);
  }
}
