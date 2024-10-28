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
    return ServerType::kMaster;
  }
  if (str == "node") {
    return ServerType::kMaster;
  }
  if (str == "room") {
    return ServerType::kRoom;
  }
  return ServerType::kUnknown;
}
}  // namespace rtype::server
