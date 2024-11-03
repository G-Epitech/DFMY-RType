/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** character_base_script.hpp
*/

#pragma once

#include "types/difficulty_data.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class EnemyBaseScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  void SetDifficultyData(DifficultyEnemyMultipliers multipliers);

  void HandleDamageTake(const std::shared_ptr<scripting::types::ScriptingContext> &context,
                        const Entity &other_entity);

  [[nodiscard]] float GetHealth() const { return health_; }

 protected:
  float speed_;
  float health_;
  float damageMultiplier_;
  float fireRateMultiplier_;
  std::chrono::duration<double> shootCooldown_;
  int scoreIncrease_;
};
}  // namespace rtype::server::game::scripts
