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
  kConnection,            ///< Connection message - TCP
  kJoinLobby,             ///< Join lobby message - TCP
  kClientJoinLobbyInfos,  ///< Client lobby infos message (udp endpoint) - TCP
  kMovement,              ///< Movement message - UDP
  kShoot,                 ///< Player shoot message - UDP
};

/// @brief Enum representing the packet messages types (server messages)
enum MessageServerType {
  kConnectionInfos,       ///< Connection infos message - TCP
  kServerJoinLobbyInfos,  ///< Join lobby infos message (udp endpoint) - TCP
  kGameStart,             ///< Game start message - TCP
  kGameEnd,               ///< Game end message - TCP
  kEnemiesState,          ///< Enemy state message (list) - UDP
  kPlayersState,          ///< Player state message (list) - UDP
  kBulletsState,          ///< Bullet state message (list) - UDP
};
}  // namespace rtype::sdk::game::api
