/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_base_script.cpp
*/

#include "enemy_base_script.hpp"

#include "scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"
#include "scripts/projectiles/default_projectile_script.hpp"

void rtype::server::game::scripts::EnemyBaseScript::SetDifficultyData(
    rtype::server::game::DifficultyEnemyMultipliers multipliers) {
  speed_ *= multipliers.speed;
  health_ *= multipliers.health;
  damageMultiplier_ = multipliers.damage;
  fireRateMultiplier_ = multipliers.fireRate;
  shootCooldown_ = std::chrono::duration<double>(shootCooldown_ / fireRateMultiplier_);
}

void rtype::server::game::scripts::EnemyBaseScript::HandleDamageTake(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const Entity& other_entity) {
  auto scriptPool =
      context->registry->GetComponent<scripting::components::ScriptPool>(other_entity);

  if (!scriptPool.has_value() || !scriptPool.value()) {
    return;
  }
  auto otherScript = scriptPool.value()->GetScript<scripts::DefaultProjectileScript>();
  health_ -= otherScript->GetDamage();

  if (health_ <= 0) {
    context->registry->DestroyEntity(context->me);
    auto projectileOwner = otherScript->GetOwnerId();
    if (!context->registry->HasEntityAtIndex(projectileOwner)) {
      return;
    }
    auto ownerEntity = context->registry->EntityFromIndex(projectileOwner);
    auto ownerScriptPool =
        context->registry->GetComponent<scripting::components::ScriptPool>(ownerEntity);
    if (!ownerScriptPool.has_value() || !ownerScriptPool.value()) {
      return;
    }
    auto ownerScript = ownerScriptPool.value()->GetScript<scripts::PlayerScript>();
    ownerScript->IncreaseScore(scoreIncrease_);
  }
}
