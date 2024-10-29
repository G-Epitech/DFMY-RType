/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

using namespace rtype::server;

RoomCtxProps::RoomCtxProps(std::size_t ticks, std::string token, std::size_t id, std::size_t maxPlayers, std::size_t difficulty)
    : ticks(ticks), token(std::move(token)), id(id), maxPlayers(maxPlayers), difficulty(difficulty) {}

RoomCtxProps::RoomCtxProps() : ticks(0), id(0), maxPlayers(0), difficulty(0) {}
