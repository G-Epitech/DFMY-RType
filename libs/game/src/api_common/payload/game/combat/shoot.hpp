/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** shoot.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/src/types/shoot.hpp"

namespace rtype::sdk::game::api_common::payload {
/// @brief Shoot payload
struct Shoot {
  /// @brief Entity id
  std::size_t entityId;
  /// @brief Shoot type
  types::ShootType type;
};
}  // namespace rtype::sdk::game::api_common::payload
