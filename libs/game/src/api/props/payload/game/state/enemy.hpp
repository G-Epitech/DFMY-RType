/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/enemies.hpp"

using namespace zygarde::core::types;

namespace rtype::sdk::game::api::payload {
/// @brief Payload for enemy state - Link to RoomToClientMsgType::kMsgTypeRTCEnemiesState
struct EnemyState {
  std::size_t entityId = 0;                              ///< @brief The entity id of the enemy
  Vector2f position;                                     ///< @brief The position of the enemy
  Vector2f velocity;                                     ///< @brief The velocity of the enemy
  types::EnemyType enemyType = types::EnemyType::kPata;  ///< @brief The type of the enemy
  std::size_t health = 0;                                ///< @brief The health of the enemy
};
}  // namespace rtype::sdk::game::api::payload
