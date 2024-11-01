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
  fireRate_ *= multipliers.fireRate;
  damage_ *= multipliers.damage;
  speed_ *= multipliers.speed;
}
