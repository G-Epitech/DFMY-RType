/*
** EPITECH PROJECT, 2024
** refresh.hpp
** File description:
** refresh header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Refresh information - Link to ClientToMasterMsgType::kMsgTypeCTMRefreshInfos
struct RefreshInfos {
  bool infoGame;
  bool infoRooms;
};
}  // namespace rtype::sdk::game::api::payload
