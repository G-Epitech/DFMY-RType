/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** shoot.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/bullet.hpp"

namespace rtype::sdk::game::api::payload {
/// @brief Shoot payload
struct Shoot {
  /// @brief Entity id
  std::size_t entityId;
  /// @brief Shoot type
  types::BulletType type;
};
}  // namespace rtype::sdk::game::api::payload
