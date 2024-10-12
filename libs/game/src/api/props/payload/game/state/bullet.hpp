/*
** EPITECH PROJECT, 2024
** bullet.hpp
** File description:
** bullet class
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/bullet.hpp"
#include "libs/game/src/utils/types/vector/vector_2f.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Payload for enemy state
struct BulletState {
  /// @brief The entity id of the enemy
  std::size_t entityId = 0;
  /// @brief The position of the enemy
  utils::types::vector_2f position;
  /// @brief The type of the bullet
  types::BulletType bulletType = types::BulletType::kCommon;
};
}  // namespace rtype::sdk::game::api::payload
