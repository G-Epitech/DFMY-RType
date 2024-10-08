/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace rtype::client::components {

/// @brief Drawable Component use in an ECS
struct Drawable {
  /// @brief Texture to render.
  sf::Texture texture;
  /// @brief Text to render.
  sf::Text text;
};
}  // namespace rtype::client::components
