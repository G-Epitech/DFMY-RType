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

namespace rtype::sdk::game::api_common::payload {
/// @brief Payload for player state
struct PlayerState {
  /// @brief The entity id of the player
  std::size_t entityId;
  /// @brief The position of the player
  utils::types::vector_2f position;
  /// @brief The health of the player
  std::size_t health;
};
}  // namespace rtype::sdk::game::api_common::payload
