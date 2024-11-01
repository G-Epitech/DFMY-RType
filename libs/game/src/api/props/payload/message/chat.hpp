/*
** EPITECH PROJECT, 2024
** chat.hpp
** File description:
** chat header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Message send by a user in a chat - Link to RoomToClientMsgType::kMsgTypeRTCChatMessage
struct ChatMessage {
  char username[20];
  char message[100];
};
}  // namespace rtype::sdk::game::api::payload
