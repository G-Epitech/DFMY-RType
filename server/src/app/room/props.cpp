/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

using namespace rtype::server;

RoomCtxProps::RoomCtxProps(std::size_t ticks, std::string token, std::size_t id)
    : ticks(ticks), token(token), id(id) {}

RoomCtxProps::RoomCtxProps() : ticks(0), id(0) {}
