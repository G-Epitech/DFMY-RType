/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** server_types.cpp
*/

#include "server_types.hpp"

#include <stdexcept>

namespace rtype::server {
ServerType StringToServerType(const std::string &str) {
  if (str == "master") {
    return rtype::server::ServerType::kMaster;
  }
  if (str == "lobby") {
    return rtype::server::ServerType::kLobby;
  }
  return rtype::server::ServerType::kUnknown;
}
}  // namespace rtype::server
