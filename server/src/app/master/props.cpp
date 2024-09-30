/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

using namespace rtype::server;

MasterCtxProps::MasterCtxProps(std::size_t maxGames, std::size_t ticks)
    : maxGames{maxGames}, ticks{ticks} {}

MasterCtxProps::MasterCtxProps() : maxGames(0), ticks(0) {}
