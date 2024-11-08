/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootScript.cpp
*/

#include "shoot_helper.hpp"

#include "core/components/position/position.hpp"
#include "scripting/components/pool/script_pool.hpp"
#include "scripts/projectiles/default_projectile_script.hpp"

using namespace rtype::server::game::scripts;

void ShootHelper::SpawnBullet(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                              const core::types::Vector3f& position_offset, float damage_multiplier,
                              const std::string& projectile_archetype) {
  const core::types::Vector3f projectilePos = GetProjectilePosition(context, position_offset);

  zygarde::core::archetypes::ArchetypeManager::ScheduleInvocationParams params;
  params.archetypeName = projectile_archetype;
  params.registryAttachCallback = [projectilePos, damage_multiplier, context](
                                      const std::shared_ptr<zygarde::Registry>& registry,
                                      const zygarde::Entity& entity) -> void {
    auto positionComponent = registry->GetComponent<core::components::Position>(entity);
    if (positionComponent.has_value() && positionComponent.value()) {
      (*positionComponent)->point = projectilePos;
    }
    auto scriptPool = registry->GetComponent<scripting::components::ScriptPool>(entity);
    if (!scriptPool.has_value() || !scriptPool.value()) {
      return;
    }
    auto script = scriptPool.value()->GetScript<DefaultProjectileScript>();
    script->SetDamage(script->GetDamage() * damage_multiplier);
    script->SetOwnerId(static_cast<std::size_t>(context->me));
  };
  context->archetypeManager->ScheduleInvocation(params);
}

core::types::Vector3f ShootHelper::GetProjectilePosition(
    const std::shared_ptr<scripting::types::ScriptingContext>& context,
    const core::types::Vector3f& position_offset) {
  auto position = context->registry->GetComponent<core::components::Position>(context->me);

  if (!position.has_value() || !position.value()) {
    return core::types::Vector3f{};
  }
  return {(*position)->point + position_offset};
}
