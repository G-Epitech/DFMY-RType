/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** time.hpp
*/

#pragma once

#include <chrono>

namespace rtype::client::utils {
/// @brief Type representing the time elapsed between two frames
typedef std::chrono::nanoseconds DeltaTime;
}  // namespace rtype::client::utils
