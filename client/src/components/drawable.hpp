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

enum ViewType {
  GAME,
  HUD,
};

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

struct Rectangle {
  sf::Color color;
  sf::Vector2f size;
};

/// @brief Drawable Component use in an ECS
struct Drawable {
  /// @brief Drawable variant.
  std::variant<Texture, Text, Rectangle> drawable;
  /// @brief Current bounds of the drawable.
  sf::FloatRect bounds = {0, 0, 0, 0};
  /// @brief View type of the drawable.
  ViewType view = ViewType::GAME;
};
}  // namespace rtype::client::components
