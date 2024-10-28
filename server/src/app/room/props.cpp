/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

using namespace rtype::server;

RoomCtxProps::RoomCtxProps(std::size_t ticks, std::string token) : ticks(ticks), token(token) {}

RoomCtxProps::RoomCtxProps() : ticks(0) {}
