/*
** EPITECH PROJECT, 2024
** room.hpp
** File description:
** room header
*/

#pragma once

#include <cstdint>

namespace rtype::sdk::game::api::payload {
/// @brief Register room to node - Link to RoomToNodeMsgType::kMsgTypeRTNRegisterRoom
struct RegisterRoom {
  std::uint64_t id;       ///< Room ID
  char token[30];         ///< Room token to register to node
  unsigned int gamePort;  ///< Room port (UDP)
  unsigned int chatPort;  ///< Chat port (TCP)
};

/// @brief Register new room to master - Link to NodeToMasterMsgType::kMsgTypeNTMRegisterNewRoom
struct RegisterNewRoom {
  std::uint64_t id;         ///< Room ID
  char name[20];            ///< Room name
  unsigned int nbPlayers;   ///< Number of players in the room to start the game
  unsigned int difficulty;  ///< Difficulty of the room
  unsigned int gamePort;    ///< Room port (UDP)
  unsigned int chatPort;    ///< Chat port (TCP)
};
}  // namespace rtype::sdk::game::api::payload
