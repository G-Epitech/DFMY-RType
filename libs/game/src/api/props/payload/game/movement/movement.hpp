/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** movement.hpp
*/

#pragma once

#include <cstddef>

#include "libs/zygarde/src/core/types/vector/vector.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Movement payload - Link to ClientToRoomMsgType::kMsgTypeCTRPlayerMove
struct Movement {
  std::size_t entityId = 0;                  ///< @brief The entity id
  zygarde::core::types::Vector2f direction;  ///< @brief The new position
};
}  // namespace rtype::sdk::game::api::payload
