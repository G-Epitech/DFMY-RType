/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** enemy_spawned.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"
#include "libs/game_types/src/enemies.hpp"
#include "libs/utils/src/types/vector/vector_2f.hpp"

using namespace rtype::sdk;

namespace rtype::sdk::api_common::payload {
/// @brief Payload for enemy spawn
struct EXPORT_API_COMMON_SDK_API EnemySpawn {
  /// @brief The entity id of the enemy
  std::size_t entityId;
  /// @brief The position of the enemy
  utils::types::vector_2f position;
  /// @brief The type of the enemy
  game::types::EnemyType enemyType;

  /**
   * @brief Construct a new Enemy Spawn object
   * @param entityId Id of the entity
   * @param position Position of the entity
   * @param enemyType Type of the enemy
   */
  EnemySpawn(std::size_t entityId, utils::types::vector_2f position,
             game::types::EnemyType enemyType);
};
}  // namespace rtype::sdk::api_common::payload
