/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** filepaths.hpp
*/

#pragma once

#include <string>

namespace rtype::server {
/// @brief Filepaths for archetypes
constexpr const char* kDirectoryEnemyArchetypes = "/game_files/archetypes/enemies/";
constexpr const char* kDirectoryPlayerArchetypes = "/game_files/archetypes/players/";
constexpr const char* kDirectoryProjectileArchetypes = "/game_files/archetypes/projectiles/";
constexpr const char* kDirectoryPowerUpArchetypes = "/game_files/archetypes/powerups/";

/// @brief Filepaths for levels
constexpr const char* kDirectoryLevels = "/game_files/levels/";

/// @brief Filepaths for difficulties
constexpr const char* kDirectoryDifficulties = "/game_files/difficulties/";
}  // namespace rtype::server
