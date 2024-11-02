/*
** EPITECH PROJECT, 2024
** send.hpp
** File description:
** send header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Send a messages to all users in a room - Link to
/// ClientToRoomMsgType::kMsgTypeCTRSendMessage
struct SendMessage {
  char message[100];
};
}  // namespace rtype::sdk::game::api::payload
