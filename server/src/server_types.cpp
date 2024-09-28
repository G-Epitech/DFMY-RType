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
  if (str == "director") {
    return rtype::server::ServerType::kDirector;
  }
  if (str == "lobby") {
    return rtype::server::ServerType::kLobby;
  }
  throw std::invalid_argument("Invalid ServerType string: " + str);
}
}  // namespace rtype::server
