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
enum class ServerType { kUnknown, kMaster, kNode, kRoom };

/**
 * Convert string to ServerType
 * @param str string to convert
 * @return ServerType
 */
ServerType StringToServerType(const std::string &str);
}  // namespace rtype::server
