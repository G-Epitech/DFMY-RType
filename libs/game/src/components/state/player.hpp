/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_state.hpp
*/

#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "libs/game/src/components/props/powerup.hpp"
#include "libs/game/src/components/props/projectile.hpp"
#include "libs/game/src/types/game_entities.hpp"
#include "libs/game/src/types/projectile.hpp"

namespace rtype::sdk::game::components {
/// @brief Player collision data
struct PlayerCollisionData {
  /// @brief The type of the entity collided with
  rtype::sdk::game::types::GameEntityType collidedType;
  /// @brief The id of the entity collided with
  int collidedId;
  /// @brief The properties of the entity collided with
  std::variant<ProjectilePropsComponent, PowerupPropsComponent>
      collidedProps;
};

/// @brief Player collisions state component
struct PlayerCollisionStateComponent {
  /// @brief The collisions data
  std::optional<std::vector<PlayerCollisionData>> collisionsData;
};
}  // namespace rtype::sdk::game::components
