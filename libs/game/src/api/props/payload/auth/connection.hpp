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
}  // namespace rtype::sdk::game::api::payload
