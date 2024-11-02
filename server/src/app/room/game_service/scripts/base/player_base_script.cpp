/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** character_base_script.cpp
*/

#include "player_base_script.hpp"

using namespace rtype::server::game::scripts;

void rtype::server::game::scripts::PlayerBaseScript::SetDifficultyData(
    rtype::server::game::DifficultyPlayerMultipliers multipliers) {
  health_ *= multipliers.health;
  speed_ *= multipliers.speed;
  fireRateMultiplier_ = multipliers.fireRate;
  damageMultiplier_ = multipliers.damage;
  ComputeShootCooldown();
}

void PlayerBaseScript::ComputeShootCooldown() {
  if (fireRateMultiplier_ != 0 && shootCooldown_ != std::chrono::nanoseconds::zero()) {
    shootCooldown_ =
        std::chrono::duration_cast<std::chrono::nanoseconds>(shootCooldown_ / fireRateMultiplier_);
  }
}
