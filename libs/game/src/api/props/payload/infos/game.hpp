/*
** EPITECH PROJECT, 2024
** game.hpp
** File description:
** game header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
struct Score {
  char name[20];  ///< The name of the room
  int64_t score;  ///< The score of the players
  bool win;       ///< The win status of the game
};

/// @brief Game information - Link to MasterToClientMsgType::kMsgTypeMTCInfoGame
struct InfoGame {
  unsigned int nbUsers;  ///< Number of users in the game
  Score leaderboard[5];  ///< The leaderboard of the game
};
}  // namespace rtype::sdk::game::api::payload
