/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** server_types.cpp
*/

#include "server_types.hpp"

#include <iostream>
#include <stdexcept>

namespace rtype::server {
ServerType StringToServerType(const std::string &str) {
  if (str == "allocator") {
    return rtype::server::ServerType::kAllocator;
  }
  if (str == "lobby") {
    return rtype::server::ServerType::kLobby;
  }
  throw std::invalid_argument("Invalid ServerType string: " + str);
}
}  // namespace rtype::server
