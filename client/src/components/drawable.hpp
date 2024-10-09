/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

namespace rtype::client::components {

/// @brief Text Component use in an ECS
struct Text {
  /// @brief Text to display
  std::string text;
  /// @brief Font name to use
  std::string fontName;
  /// @brief Character size of the text
  unsigned int characterSize = 12;
  /// @brief Color of the text
  sf::Color color = sf::Color::White;
};

/// @brief Texture Component use in an ECS
struct Texture {
  /// @brief Path to the texture
  std::string path;
};

/// @brief Drawable Component use in an ECS
struct Drawable {
  /// @brief Drawable variant.
  std::variant<Texture, Text> drawable;
  /// @brief Current bounds of the drawable.
  sf::FloatRect bounds = {0, 0, 0, 0};
};
}  // namespace rtype::client::components
