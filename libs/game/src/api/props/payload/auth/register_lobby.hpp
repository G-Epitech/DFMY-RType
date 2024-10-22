/*
** EPITECH PROJECT, 2024
** register.hpp
** File description:
** register class
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Connection payload
struct RegisterLobby {
  unsigned lobbyId;  // Id of the lobby that is registered
};
}  // namespace rtype::sdk::game::api::payload
