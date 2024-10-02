/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game_end.cpp
*/

#include "game_end.hpp"

using namespace rtype::sdk::api_common::payload;

CoopGameEnd::CoopGameEnd(std::size_t score, time_t time, bool win)
    : score{score}, time{time}, win{win} {}
