/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy.hpp
*/

#pragma once

#include <cstddef>

using namespace zygarde::core::types;

namespace rtype::sdk::game::api::payload {
/// @brief Payload for player state - Link to RoomToClientMsgType::kMsgTypeRTCPlayersState
struct PlayerState {
  std::size_t entityId = 0;  ///< @brief The entity id of the player
  Vector2f position;         ///< @brief The position of the player
  std::size_t health = 0;    ///< @brief The health of the player
  Vector2f velocity;         ///< @brief The velocity of the player
};
}  // namespace rtype::sdk::game::api::payload
