/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** fire_rate.hpp
*/

#pragma once

#include <chrono>

#include "core.hpp"

namespace rtype::sdk::game::utils {
EXPORT_GAME_SDK_API std::chrono::nanoseconds GetFireRate(const float &fire_rate);
}
