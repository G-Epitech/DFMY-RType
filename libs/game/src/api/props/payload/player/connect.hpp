/*
** EPITECH PROJECT, 2024
** connect.hpp
** File description:
** connect class
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Connect a player - Link to ClientToMasterMsgType::kMsgTypeCTMConnect
struct PlayerConnect {
  char username[20];  ///< The player username
};
}  // namespace rtype::sdk::game::api::payload
