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

struct JoinLobbyInfos {
  char ip[16];
  unsigned port;
};
}  // namespace rtype::sdk::game::api::payload
