/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include <string>
namespace rtype::client::components {
struct SelectContainer {
  /// @brief Is the container expanded
  bool expanded = false;
  /// @brief Current label of the container
  std::string label;
  /// @brief Current value of the container
  std::string selectId;
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
  /// @brief Select id of the option
  std::string selectId;
};
}  // namespace rtype::client::components
