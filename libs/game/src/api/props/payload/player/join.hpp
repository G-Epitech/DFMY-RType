/*
** EPITECH PROJECT, 2024
** join.hpp
** File description:
** join class
*/

#pragma once

#include <cstdint>

namespace rtype::sdk::game::api::payload {
/// @brief Player join room - Link to NodeToRoomMsgType::kMsgTypeNTRPlayerJoin and
struct PlayerJoin {
  std::uint64_t id;   ///< The player id
  char username[20];  ///< The player username
  char ip[16];        ///< The player ip
};

/// @brief Player join room - Link to MasterToNodeMsgType::kMsgTypeMTNPlayerJoinRoom
struct PlayerJoinRoom {
  std::uint64_t id;      ///< The player id
  char username[20];     ///< The player username
  char ip[16];           ///< The player ip
  std::uint64_t roomId;  ///< The room id
};
}  // namespace rtype::sdk::game::api::payload
