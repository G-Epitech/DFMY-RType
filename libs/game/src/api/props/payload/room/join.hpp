/*
** EPITECH PROJECT, 2024
** join.hpp
** File description:
** join class
*/

#pragma once

#include <cstdint>

namespace rtype::sdk::game::api::payload {
/// @brief Join room - Link to ClientToMasterMsgType::kMsgTypeCTMJoinRoom
struct JoinRoom {
  std::uint64_t nodeId;
  std::uint64_t roomId;
};
}  // namespace rtype::sdk::game::api::payload
