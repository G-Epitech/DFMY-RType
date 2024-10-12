/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_state.hpp
*/

#pragma once

#include <optional>
#include <vector>

#include "libs/game/src/components/props/projectile.hpp"
#include "libs/game/src/types/game_entities.hpp"

namespace rtype::sdk::game::components {
struct EnemyCollisionData {
  rtype::sdk::game::types::GameEntityType collidedType;
  int collidedId;
  ProjectilePropsComponent collidedProps;
};

struct EnemyCollisionStateComponent {
  std::optional<std::vector<EnemyCollisionData>> collisionsData;
};
}  // namespace rtype::sdk::game::components
