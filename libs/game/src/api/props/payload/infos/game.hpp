/*
** EPITECH PROJECT, 2024
** game.hpp
** File description:
** game header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Game information - Link to MasterToClientMsgType::kMsgTypeMTCInfoGame
struct InfoGame {
  unsigned int nbUsers;  ///< Number of users in the game
};
}  // namespace rtype::sdk::game::api::payload
