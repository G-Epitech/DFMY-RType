/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2i
*/

#pragma once

#include <cmath>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_3f.hpp"

namespace zygarde::core::types {
class EXPORT_ZYGARDE_API Vector2i final {
 public:
  constexpr Vector2i() = default;
  ~Vector2i() = default;

  /**
   * @brief Construct a new Vector2i object
   * @param x x value
   * @param y y value
   */
  constexpr Vector2i(int x, int y) : x{x}, y{y} {}

 public:
  /**
   * @brief Addition operator
   * @param vec Vector2i object
   * @return Vector2i
   */
  Vector2i operator+(const Vector2i &vec) const noexcept;

  /**
   * @brief Addition assignment operator
   * @param vec Vector2i object
   * @return Vector2i&
   */
  Vector2i &operator+=(const Vector2i &vec) noexcept;

  /**
   * @brief Subtraction operator
   * @param vec Vector2i object
   * @return Vector2i
   */
  Vector2i operator-(const Vector2i &vec) const noexcept;

  /**
   * @brief Subtraction assignment operator
   * @param vec Vector2i object
   * @return Vector2i&
   */
  Vector2i &operator-=(const Vector2i &vec) noexcept;

  /**
   * @brief Multiplication operator
   * @param scalar scalar value
   * @return Vector2i
   */
  Vector2i operator*(int scalar) const noexcept;

  /**
   * @brief Multiplication assignment operator
   * @param scalar scalar value
   * @return Vector2i&
   */
  Vector2i &operator*=(float scalar) noexcept;

  /**
   * @brief Multiplication operator
   * @param vec Vector2i object
   * @return Vector2i
   */
  Vector2i operator*(const Vector2i &vec) const noexcept;

  /**
   * @brief Multiplication assignment operator
   * @param vec Vector2i object
   * @return Vector2i&
   */
  Vector2i &operator*=(const Vector2i &vec) noexcept;

  /**
   * @brief Equality operator
   * @param vec Vector2i object
   * @return bool
   */
  bool operator==(const Vector2i &vec) const noexcept;

  /**
   * @brief Division operator
   * @param scalar scalar value
   * @return Vector2i
   */
  Vector2i operator/(float scalar) const noexcept;

  /**
   * @brief Division assignment operator
   * @param scalar scalar value
   * @return Vector2i&
   */
  Vector2i &operator/=(float scalar) noexcept;

  /**
   * @brief Get the zero vector
   * @return Vector2i
   */
  static constexpr Vector2i zero() noexcept { return {0, 0}; }

  /**
   * @brief Get the one vector
   * @return
   */
  static constexpr Vector2i one() noexcept { return {1, 1}; }

  /**
   * @brief Get the up vector
   * @return
   */
  static constexpr Vector2i up() noexcept { return {0, 1}; }

  /**
   * @brief Get the down vector
   * @return
   */
  static constexpr Vector2i down() noexcept { return {0, -1}; }

  /**
   * @brief Get the left vector
   * @return
   */
  static constexpr Vector2i left() noexcept { return {-1, 0}; }

  /**
   * @brief Get the right vector
   * @return
   */
  static constexpr Vector2i right() noexcept { return {1, 0}; }

  /**
   * @brief Dot product
   * @param vec1 Vector2i object
   * @param vec2 Vector2i object
   * @return dot product
   */
  [[nodiscard]] static float dot(const Vector2i &vec1, const Vector2i &vec2) noexcept;

  /**
   * @brief Distance between two vectors
   * @param vec1 Vector2i object
   * @param vec2 Vector2i object
   * @return distance
   */
  [[nodiscard]] static double distance(const Vector2i &vec1, const Vector2i &vec2) noexcept;

  /**
   * @brief Normalize a vector
   * @param vec Vector2i object
   * @return normalized vector
   */
  [[nodiscard]] Vector2i normalize(const Vector2i &vec) const noexcept;

  /**
   * @brief Get the magnitude of the vector
   * @return magnitude
   */
  [[nodiscard]] float magnitude() const noexcept;

  /**
   * @brief Get the normalized vector
   * @return normalized vector
   */
  [[nodiscard]] Vector2i normalized() const noexcept;

 public:
  /// @brief x value
  int x = 0;
  /// @brief y value
  int y = 0;
};
}  // namespace zygarde::core::types
