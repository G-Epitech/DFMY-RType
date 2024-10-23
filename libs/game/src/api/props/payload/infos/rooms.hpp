/*
** EPITECH PROJECT, 2024
** rooms.hpp
** File description:
** rooms header
*/

#pragma once

#include <cstdint>

namespace rtype::sdk::game::api::payload {
/// @brief Room information - Link to MasterToClientMsgType::kMsgTypeMTCInfoRoom
struct InfoRoom {
  char ip[16];        ///< IP of the room
  unsigned int port;  ///< Port of the room
};

struct InfoConnectRoom {
  unsigned int port;  ///< Port of the client in the room
};

/// @brief Room status - Internal use for InfoRooms
struct RoomStatus {
  std::uint64_t id;           ///< Room ID
  char name[20];              ///< Room name
  unsigned int nbPlayersMax;  ///< Maximum number of players in the room
  unsigned int nbPlayers;     ///< Number of players in the room
  unsigned int difficulty;    ///< Difficulty of the room
};

/// @brief Rooms information - Link to MasterToClientMsgType::kMsgTypeMTCInfoRooms
struct InfoRooms {
  unsigned int nbRooms;  ///< Number of rooms (max 25)
  bool canCreate;        ///< Can create a room
  RoomStatus rooms[25];  ///< Rooms
};
}  // namespace rtype::sdk::game::api::payload
