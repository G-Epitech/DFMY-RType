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
constexpr const char* kEnemyArchetypesDirectory = "/game_files/archetypes/enemies/";
constexpr const char* kPlayerArchetypesDirectory = "/game_files/archetypes/players/";
constexpr const char* kProjectileArchetypesDirectory = "/game_files/archetypes/projectiles/";
constexpr const char* kPowerUpArchetypesDirectory = "/game_files/archetypes/powerups/";

/// @brief Filepaths for levels
constexpr const char* kLevelFolderPath = "/game_files/levels/";

/// @brief Filepaths for difficulties
constexpr const char* kDifficultyFolderPath = "/game_files/difficulties/";
}  // namespace rtype::server
