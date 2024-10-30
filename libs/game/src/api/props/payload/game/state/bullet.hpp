/*
** EPITECH PROJECT, 2024
** bullet.hpp
** File description:
** bullet class
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/projectile.hpp"
#include "libs/game/src/utils/types/vector/vector_2f.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Payload for bullet state - Link to RoomToClientMsgType::kMsgTypeRTCBulletsState
struct BulletState {
  std::size_t entityId = 0;          ///< @brief The entity id of the enemy
  utils::types::vector_2f position;  ///< @brief The position of the enemy
  types::ProjectileType bulletType =
      types::ProjectileType::kPlayerCommon;  ///< @brief The type of the bullet
};
}  // namespace rtype::sdk::game::api::payload
