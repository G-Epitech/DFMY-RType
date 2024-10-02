/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_start.cpp
*/

#include "game_start.hpp"

#include <utility>

using namespace rtype::sdk::api_common::payload;

GameStart::GameStart(std::size_t nbPlayers, std::string message)
    : nbPlayers{nbPlayers}, message{std::move(message)} {}
