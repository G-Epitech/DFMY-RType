/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** vector_2_f.hpp
*/

#pragma once

#include "libs/utils/src/api.hpp"

namespace rtype::sdk::utils::types {
/// @brief A 2D vector of integers
struct EXPORT_UTILS_SDK_API vector_2i {
  /// @brief The x coordinate of the vector
  int x = 0;
  /// @brief The y coordinate of the vector
  int y = 0;

  /**
   * @brief Construct a new vector_2f object
   * @param x x coordinate
   * @param y y coordinate
   */
  vector_2i(int x, int y);

  /**
   * @brief Construct a new vector_2i object with default values
   */
  vector_2i() = default;
};
}  // namespace rtype::sdk::utils::types
