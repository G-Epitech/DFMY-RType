/*
** EPITECH PROJECT, 2024
** join_lobby.hpp
** File description:
** join_lobby class
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Join a lobby payload
struct JoinLobby {
  unsigned lobbyId;  // Id of the lobby to join
};

/// @brief Join a lobby infos payload
struct JoinLobbyInfos {
  char ip[16];    // Ip of the client/server to join (udp)
  unsigned port;  // Port of the client/server to join (udp)
};
}  // namespace rtype::sdk::game::api::payload
