/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Vector3f.hpp
*/

#pragma once

#include "libs/zygarde/src/api.hpp"

namespace zygarde::core::types {
class EXPORT_ZYGARDE_API Vector3f final {
 public:
  constexpr Vector3f() = default;
  ~Vector3f() = default;

  /**
   * @brief Construct a new Vector3f object
   */
  constexpr Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

  /**
   * @brief Add Vector3f object by another Vector3f object
   */
  Vector3f operator+(const Vector3f& other) const noexcept;

  /**
   * @brief Subtract Vector3f object by another Vector3f object
   */
  Vector3f operator-(const Vector3f& other) const noexcept;

  /**
   * @brief Multiply Vector3f object by another Vector3f object
   */
  Vector3f operator*(const Vector3f& other) const noexcept;

  /**
   * @brief Divide Vector3f object by another Vector3f object
   */
  Vector3f operator/(const Vector3f& other) const noexcept;

  /**
   * @brief Add Vector3f object by another Vector3f object
   */
  Vector3f& operator+=(const Vector3f& other) noexcept;

  /**
   * @brief Subtract Vector3f object by another Vector3f object
   */
  Vector3f& operator-=(const Vector3f& other) noexcept;

  /**
   * @brief Multiply Vector3f object by another Vector3f object
   */
  Vector3f& operator*=(const Vector3f& other) noexcept;

  /**
   * @brief Divide Vector3f object by another Vector3f object
   */
  Vector3f& operator/=(const Vector3f& other) noexcept;

  /**
   * @brief Get the zero vector
   */
  [[nodiscard]] static constexpr Vector3f zero() noexcept { return {0, 0, 0}; }

  /**
   * @brief Get the one vector
   */
  [[nodiscard]] static constexpr Vector3f one() noexcept { return {1, 1, 1}; }

  /**
   * @brief Get the up vector
   */
  [[nodiscard]] static constexpr Vector3f up() noexcept { return {0, 1, 0}; }

  /**
   * @brief Get the down vector
   */
  [[nodiscard]] static constexpr Vector3f down() noexcept { return {0, -1, 0}; }

  /**
   * @brief Get the left vector
   */
  [[nodiscard]] static constexpr Vector3f left() noexcept { return {-1, 0, 0}; }

  /**
   * @brief Get the right vector
   */
  [[nodiscard]] static constexpr Vector3f right() noexcept { return {1, 0, 0}; }

 public:
  /// @brief x value
  float x = 0;
  /// @brief y value
  float y = 0;
  /// @brief z value
  float z = 0;
};
}  // namespace zygarde::core::types
