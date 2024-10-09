/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

#include <variant>
#include <SFML/Graphics.hpp>

namespace rtype::client::components {

struct Text {
  /// @brief Text to display
  std::string text;
  /// @brief Character size of the text
  unsigned int characterSize = 30;
  /// @brief Color of the text
  sf::Color color = sf::Color::White;
  /// @brief Font name to use
  std::string fontName;
};

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
