/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** shoot.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/projectile.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Shoot payload - Link to ClientToRoomMsgType::kMsgTypeCTRPlayerShoot
struct Shoot {
  std::size_t entityId;        ///< @brief Entity id
  types::ProjectileType type;  ///< @brief Shoot type
};
}  // namespace rtype::sdk::game::api::payload
