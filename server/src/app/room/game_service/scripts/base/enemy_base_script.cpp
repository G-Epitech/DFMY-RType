/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_base_script.cpp
*/

#include "enemy_base_script.hpp"

void rtype::server::game::scripts::EnemyBaseScript::SetDifficultyData(
    rtype::server::game::DifficultyEnemyMultipliers multipliers) {
  speed_ *= multipliers.speed;
  health_ *= multipliers.health;
  damageMultiplier_ = multipliers.damage;
  fireRateMultiplier_ = multipliers.fireRate;
  shootCooldown_ = std::chrono::duration<double>(shootCooldown_ / fireRateMultiplier_);
}
