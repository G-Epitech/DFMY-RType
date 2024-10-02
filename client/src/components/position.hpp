/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

namespace rtype::client::components {

/// @brief Positon Component use in an ECS
struct Position {
  /// @brief X position
  float x = 0;
  /// @brief Y position
  float y = 0;
};
}  // namespace rtype::client::components
