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
/// @brief Payload for player state - Link to RoomToClientMsgType::kMsgTypeRTCPlayersState
struct PlayerState {
  std::size_t entityId = 0;          ///< @brief The entity id of the player
  utils::types::vector_2f position;  ///< @brief The position of the player
  std::size_t health = 0;            ///< @brief The health of the player
};
}  // namespace rtype::sdk::game::api::payload
