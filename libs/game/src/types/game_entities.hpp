/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** entities.hpp
*/

#pragma once

namespace rtype::sdk::game::types {
/// @brief Enum for game entity types
enum class GameEntityType {
  kPlayer = 0,
  kEnemy = 1,
  kBullet = 2,
  kPowerUp = 3,
};
}  // namespace rtype::sdk::game::types
