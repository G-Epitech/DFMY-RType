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
struct PlayerCollisionData {
  rtype::sdk::game::types::GameEntityType collidedType;
  int collidedId;
  std::variant<ProjectilePropsComponent, PowerupPropsComponent> collidedProps;
};

struct PlayerCollisionStateComponent {
  std::optional<std::vector<PlayerCollisionData>> collisionsData;
};
}  // namespace rtype::sdk::game::components
