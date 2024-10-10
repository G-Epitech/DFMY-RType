/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

#include "managers/window_manager.hpp"

namespace rtype::client::components {

/// @brief Text Component use in an ECS
struct Text {
  std::string text;                    ///< Text to display
  std::string fontName;                ///< Font name
  unsigned int characterSize = 12;     ///< Character size
  sf::Color color = sf::Color::White;  ///< Color of the text
};

/// @brief Texture Component use in an ECS
struct Texture {
  std::string path;  ///< Path to the texture
};

/// @brief Rectangle Component use in an ECS
struct Rectangle {
  sf::Color color;    ///< Color of the rectangle
  sf::Vector2f size;  ///< Size of the rectangle
};

/// @brief Drawable Component use in an ECS
struct Drawable {
  std::variant<Texture, Text, Rectangle> drawable;       ///< Drawable to display
  WindowManager::View view = WindowManager::View::GAME;  ///< View of the drawable
  sf::FloatRect bounds = {0, 0, 0, 0};                   ///< Bounds of the drawable
};
}  // namespace rtype::client::components
