/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_3f.hpp
*/

#pragma once

namespace zygarde::core::types {
class vector_3f {
 public:
  constexpr vector_3f() = default;
  ~vector_3f() = default;

  /**
   * @brief Construct a new vector_3f object
   */
  constexpr vector_3f(float x, float y, float z) : x(x), y(y), z(z) {}

  /**
   * @brief Add vector_3f object by another vector_3f object
   */
  vector_3f operator+(const vector_3f& other) const noexcept;

  /**
   * @brief Subtract vector_3f object by another vector_3f object
   */
  vector_3f operator-(const vector_3f& other) const noexcept;

  /**
   * @brief Multiply vector_3f object by another vector_3f object
   */
  vector_3f operator*(const vector_3f& other) const noexcept;

  /**
   * @brief Divide vector_3f object by another vector_3f object
   */
  vector_3f operator/(const vector_3f& other) const noexcept;

  /**
   * @brief Add vector_3f object by another vector_3f object
   */
  vector_3f& operator+=(const vector_3f& other) noexcept;

  /**
   * @brief Subtract vector_3f object by another vector_3f object
   */
  vector_3f& operator-=(const vector_3f& other) noexcept;

  /**
   * @brief Multiply vector_3f object by another vector_3f object
   */
  vector_3f& operator*=(const vector_3f& other) noexcept;

  /**
   * @brief Divide vector_3f object by another vector_3f object
   */
  vector_3f& operator/=(const vector_3f& other) noexcept;

  /**
   * @brief Get the zero vector
   */
  [[nodiscard]] static constexpr vector_3f zero() noexcept { return {0, 0, 0}; }

  /**
   * @brief Get the one vector
   */
  [[nodiscard]] static constexpr vector_3f one() noexcept { return {1, 1, 1}; }

  /**
   * @brief Get the up vector
   */
  [[nodiscard]] static constexpr vector_3f up() noexcept { return {0, 1, 0}; }

  /**
   * @brief Get the down vector
   */
  [[nodiscard]] static constexpr vector_3f down() noexcept { return {0, -1, 0}; }

  /**
   * @brief Get the left vector
   */
  [[nodiscard]] static constexpr vector_3f left() noexcept { return {-1, 0, 0}; }

  /**
   * @brief Get the right vector
   */
  [[nodiscard]] static constexpr vector_3f right() noexcept { return {1, 0, 0}; }

 public:
  /// @brief x value
  float x{0};
  /// @brief y value
  float y{0};
  /// @brief z value
  float z{0};
};
}  // namespace zygarde::core::types
