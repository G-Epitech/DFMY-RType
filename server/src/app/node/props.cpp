/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

#include <utility>

using namespace rtype::server;

NodeCtxProps::NodeCtxProps(std::size_t maxRooms, std::string token, std::string masterToken)
    : maxRooms(maxRooms), token(std::move(token)), masterToken(std::move(masterToken)) {}

NodeCtxProps::NodeCtxProps() : token() {}
