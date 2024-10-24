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
    return kMaster;
  }
  if (str == "lobby") {
    return kLobby;
  }
  return kUnknown;
}
}  // namespace rtype::server
