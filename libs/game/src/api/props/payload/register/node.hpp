/*
** EPITECH PROJECT, 2024
** node.hpp
** File description:
** node header
*/

#pragma once

namespace rtype::sdk::game::api::payload {
/// @brief Register node - Link to NodeToMasterMsgType::kMsgTypeNTMRegisterNode
struct RegisterNode {
  char name[20];   ///< Node name
  char token[30];  ///< Token to register to the master
};
}  // namespace rtype::sdk::game::api::payload
