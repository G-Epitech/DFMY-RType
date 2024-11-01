/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_base_script.cpp
*/

#include "enemy_base_script.hpp"

void rtype::server::game::scripts::EnemyBaseScript::SetDifficultyData(
    rtype::server::game::DifficultyEnemyMultipliers multipliers) {
  health_ *= multipliers.health;
  fireRate_ *= multipliers.fireRate;
  damage_ *= multipliers.damage;
  speed_ *= multipliers.speed;
}
