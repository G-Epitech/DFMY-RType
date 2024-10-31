/*
** EPITECH PROJECT, 2024
** create.hpp
** File description:
** create class
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Create room - Link to ClientToMasterMsgType::kMsgTypeCTMCreateRoom
struct CreateRoom {
  char name[20];
  unsigned int nbPlayers;
  unsigned int difficulty;
};
}  // namespace rtype::sdk::game::api::payload
