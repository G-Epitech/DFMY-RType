/*
** EPITECH PROJECT, 2024
** join.hpp
** File description:
** join class
*/

#pragma once

#include <cstdint>

namespace rtype::sdk::game::api::payload {
/// @brief Player join room - Link to MasterToNodeMsgType::kMsgTypeMTNPlayerJoin and
/// NodeToRoomMsgType::kMsgTypeNTRPlayerJoin
struct PlayerJoin {
  std::uint64_t id;   ///< The player id
  char username[20];  ///< The player username
  char ip[16];        ///< The player ip
};
}  // namespace rtype::sdk::game::api::payload
