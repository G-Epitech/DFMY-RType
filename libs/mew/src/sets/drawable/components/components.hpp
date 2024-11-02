/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_component.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

#include "libs/mew/src/managers/managers.hpp"

namespace mew::sets::drawable {

/// @brief Text Component use in an ECS
struct Text {
  std::string text;                           ///< Text to display
  std::string fontName;                       ///< Font name
  unsigned int characterSize = 12;            ///< Character size
  sf::Text::Style style = sf::Text::Regular;  ///< Style of the text
  sf::Color color = sf::Color::White;         ///< Color of the text
};

/// @brief Texture Component use in an ECS
struct Texture {
  std::string name;  ///< Path to the texture
  float scale = 1;   ///< Scale of the texture
  sf::IntRect rect;  ///< Rectangle of the texture
};

/// @brief Rectangle Component use in an ECS
struct Rectangle {
  sf::Color fillColor = sf::Color::Transparent;  ///< Color of the rectangle
  sf::Color outlineColor = sf::Color::Transparent;                        ///< Color of the outline
  float outlineThickness = 0;                    ///< Thickness of the outline
  sf::Vector2f size;                             ///< Size of the rectangle
};

/// @brief Drawable Component use in an ECS
struct Drawable {
  std::variant<Texture, Text, Rectangle> drawable;  ///< Drawable to display
  managers::WindowManager::View view =
      managers::WindowManager::View::GAME;  ///< View of the drawable
  sf::FloatRect bounds = {0, 0, 0, 0};      ///< Bounds of the drawable
  bool visible = true;                      ///< Visibility of the drawable
  unsigned int layer = 0;                   ///< Layer of the drawable
};
}  // namespace mew::sets::drawable
