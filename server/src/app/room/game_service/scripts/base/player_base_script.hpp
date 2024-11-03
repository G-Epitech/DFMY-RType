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
class PlayerBaseScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  void SetDifficultyData(DifficultyPlayerMultipliers multipliers);

  inline void GiveDamage(float damage) { health_ -= damage; }

 protected:
  void ComputeShootCooldown();

 protected:
  float health_;
  float fireRateMultiplier_;
  float damageMultiplier_;
  float speed_;
  std::chrono::nanoseconds shootCooldown_;
};
}  // namespace rtype::server::game::scripts
