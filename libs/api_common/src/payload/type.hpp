/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** type.hpp
*/

#pragma once

namespace rtype::sdk::api_common::payload {
/// @brief Enum representing the different types of payloads
enum PayloadType {
  kCollision = 0,
  kDamageDealt = 1,
  kDeath = 2,
  kGameEnd = 3,
  kGameStart = 4,
  kMovement = 5,
  kShoot = 6,
  kEnemySpawn = 7,
};
}
