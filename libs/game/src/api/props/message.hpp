/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** type.hpp
*/

#pragma once

namespace rtype::sdk::game::api {
/// @brief Enum representing the packet messages types
enum MessageType {
  kShoot = 0,
  kGameEnd = 1,
  kGameStart = 2,
  kMovement = 3,
  kEnemyState = 4,
  kPlayerState = 5,
};
}  // namespace rtype::sdk::game::api_common
