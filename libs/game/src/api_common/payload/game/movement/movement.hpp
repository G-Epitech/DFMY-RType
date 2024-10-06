/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** movement.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/utils/types/vector/vector_2f.hpp"

namespace rtype::sdk::game::api_common::payload {
/// @brief Movement payload
struct Movement {
  /// @brief The entity id
  std::size_t entityId;
  /// @brief The new position
  utils::types::vector_2f newPosition;
};
}  // namespace rtype::sdk::game::api_common::payload
