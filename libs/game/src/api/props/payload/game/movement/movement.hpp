/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** movement.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/utils/types/vector/vector_2f.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Movement payload - Link to ClientToRoomMsgType::kMsgTypeCTRPlayerMove
struct Movement {
  std::size_t entityId = 0;           ///< @brief The entity id
  utils::types::vector_2f direction;  ///< @brief The new position
};
}  // namespace rtype::sdk::game::api::payload
