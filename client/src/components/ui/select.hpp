/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <optional>
#include <string>

namespace rtype::client::components {
struct SelectContainer {
  /// @brief Is the container expanded
  bool expanded = false;
  /// @brief Current selected option
  std::optional<std::string> selectedOption = std::nullopt;
  /// @brief Current value of the container
  std::string selectId;
  /// @brief Placeholder of the select when no options are available
  std::string placeholder;
  /// @brief Color when an option is selected
  sf::Color selectedColor;
  /// @brief Color when no option are available
  sf::Color disabledColor;
  /// @brief Hover color of the select
  sf::Color hoveredColor;
};

struct SelectOption {
  /// @brief Label of the option
  std::string label;
  /// @brief Value of the option
  std::string value;
  /// @brief Is the option selected
  bool selected = false;
  /// @brief Is the option hovered
  bool hovered = false;
  /// @brief Is the option disabled
  bool disabled = false;
  /// @brief Select id of the option
  std::string selectId;
};
}  // namespace rtype::client::components
