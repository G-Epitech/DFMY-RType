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
/// @brief Enemy collision data
struct EnemyCollisionData {
  /// @brief The type of the entity collided
  rtype::sdk::game::types::GameEntityType collidedType;
  /// @brief The id of the entity collided
  int collidedId;
  /// @brief The props of the entity collided
  ProjectilePropsComponent collidedProps;
};

/// @brief Enemy collision state component
struct EnemyCollisionStateComponent {
  /// @brief The entity id of the enemy
  std::optional<std::vector<EnemyCollisionData>> collisionsData;
};
}  // namespace rtype::sdk::game::components
