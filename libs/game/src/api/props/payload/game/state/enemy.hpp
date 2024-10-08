/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/enemies.hpp"
#include "libs/game/src/utils/types/vector/vector_2f.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Payload for enemy state
struct EnemyState {
  /// @brief The entity id of the enemy
  std::size_t entityId;
  /// @brief The position of the enemy
  utils::types::vector_2f position;
  /// @brief The type of the enemy
  types::EnemyType enemyType;
  /// @brief The health of the enemy
  std::size_t health;
};
}  // namespace rtype::sdk::game::api_common::payload
