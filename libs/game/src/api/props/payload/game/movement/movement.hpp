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
/// @brief Movement payload
struct Movement {
  /// @brief The entity id
  std::size_t entityId = 0;
  /// @brief The new position
  utils::types::vector_2f direction;
};
}  // namespace rtype::sdk::game::api::payload
