/*
** EPITECH PROJECT, 2024
** connection.hpp
** File description:
** connection class
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Connection payload
struct Connection {
  char pseudo[20] = "Anonymous";  // Pseudo of the player
};

/// @brief Connection infos payload
struct ConnectionInfos {
  unsigned onlinePlayers;  // Numbers of online players
};
}  // namespace rtype::sdk::game::api::payload
