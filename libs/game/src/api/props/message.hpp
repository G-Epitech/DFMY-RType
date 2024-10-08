/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** type.hpp
*/

#pragma once

namespace rtype::sdk::game::api {
/// @brief Enum representing the packet messages types (client messages)
enum MessageClientType {
  kConnection,  ///< Connection message
  kJoinLobby,   ///< Join lobby message
  kMovement,    ///< Movement message
  kShoot,       ///< Player shoot message
};

/// @brief Enum representing the packet messages types (server messages)
enum MessageServerType {
  kJoinLobbyInfos,  ///< Join lobby infos message
  kGameStart,       ///< Game start message
  kGameEnd,         ///< Game end message
  kEnemyState,      ///< Enemy state message (list)
  kPlayerState,     ///< Player state message (list)
};
}  // namespace rtype::sdk::game::api
