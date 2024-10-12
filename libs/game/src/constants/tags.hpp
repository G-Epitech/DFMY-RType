/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** tags.hpp
*/

#pragma once

#include <string>

namespace rtype::sdk::game::constants {
inline constexpr std::string_view kPlayerTag = "player";
inline constexpr std::string_view kEnemyTag = "enemy";
inline constexpr std::string_view kEnemyBulletTag = "enemy_bullet";
inline constexpr std::string_view kPlayerBulletTag = "player_bullet";
inline constexpr std::string_view kPowerUpTag = "power_up";
}  // namespace rtype::sdk::game::constants
