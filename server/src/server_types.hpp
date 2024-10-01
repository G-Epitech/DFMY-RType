/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** server_types.hpp
*/

#pragma once

#include <string>

namespace rtype::server {
/**
 * Server type enum
 */
enum ServerType { kUnknown = 0, kMaster = 1, kLobby = 2 };

/**
 * Convert string to ServerType
 * @param str string to convert
 * @return ServerType
 */
ServerType StringToServerType(const std::string &str);
}  // namespace rtype::server
