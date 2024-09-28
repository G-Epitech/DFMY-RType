/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** server_types.hpp
*/

#pragma once

#include <string>

namespace rtype::server {
enum ServerType { kDirector = 1, kLobby = 2 };

ServerType StringToServerType(const std::string &str);

}  // namespace rtype::server
