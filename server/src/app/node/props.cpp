/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

#include <utility>

using namespace rtype::server;

NodeCtxProps::NodeCtxProps(std::size_t maxRooms, std::string token, std::string masterToken,
                           std::string binaryPath, std::string ip)
    : maxRooms(maxRooms),
      token(std::move(token)),
      masterToken(std::move(masterToken)),
      binaryPath(std::move(binaryPath)),
      ip(std::move(ip)) {}

NodeCtxProps::NodeCtxProps() : token() {}
