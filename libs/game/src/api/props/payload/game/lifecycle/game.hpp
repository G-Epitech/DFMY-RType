/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_end.hpp
*/

#pragma once

#include <cstddef>
#include <ctime>

namespace rtype::sdk::game::api::payload {
/// @brief End of the game - Link to multiple messages
struct GameEnd {
  std::size_t score;  ///< @brief Score of the player
  time_t time;        ///< @brief Time taken to finish the game
  bool win;           ///< @brief Whether the player won or not
};

/// @brief End of the game - Link to NodeToMasterMsgType::kMsgTypeNTMRoomGameEnd
struct RoomGameEnd {
  std::uint64_t id;   ///< @brief The id of the room
  std::size_t score;  ///< @brief Score of the player
  time_t time;        ///< @brief Time taken to finish the game
  bool win;           ///< @brief Whether the player won or not
};

/// @brief Start of the game - Link to NodeToMasterMsgType::kMsgTypeNTMRoomGameStart
struct RoomGameStart {
  std::uint64_t id;  ///< @brief The id of the room
};
}  // namespace rtype::sdk::game::api::payload
