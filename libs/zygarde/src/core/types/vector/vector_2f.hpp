/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2_f.hpp
*/

#pragma once

#include <cmath>

#include "libs/zygarde/src/api.hpp"

namespace zygarde::core::types {
class EXPORT_ZYGARDE_API vector_2f final {
 public:
  constexpr vector_2f() = default;
  ~vector_2f() = default;

  /**
   * @brief Construct a new vector_2f object
   * @param x x value
   * @param y y value
   */
  constexpr vector_2f(float x, float y) : x(x), y(y) {};

 public:
  /**
   * @brief Addition operator
   * @param vec vector_2f object
   * @return vector_2f
   */
  vector_2f operator+(const vector_2f &vec) const noexcept;

  /**
   * @brief Addition assignment operator
   * @param vec vector_2f object
   * @return vector_2f&
   */
  vector_2f &operator+=(const vector_2f &vec) noexcept;

  /**
   * @brief Subtraction operator
   * @param vec vector_2f object
   * @return vector_2f
   */
  vector_2f operator-(const vector_2f &vec) const noexcept;

  /**
   * @brief Subtraction assignment operator
   * @param vec vector_2f object
   * @return vector_2f&
   */
  vector_2f &operator-=(const vector_2f &vec) noexcept;

  /**
   * @brief Multiplication operator
   * @param scalar scalar value
   * @return vector_2f
   */
  vector_2f operator*(float scalar) const noexcept;

  /**
   * @brief Multiplication assignment operator
   * @param scalar scalar value
   * @return vector_2f&
   */
  vector_2f &operator*=(float scalar) noexcept;

  /**
   * @brief Multiplication operator
   * @param vec vector_2f object
   * @return vector_2f
   */
  vector_2f operator*(const vector_2f &vec) const noexcept;

  /**
   * @brief Multiplication assignment operator
   * @param vec vector_2f object
   * @return vector_2f&
   */
  vector_2f &operator*=(const vector_2f &vec) noexcept;

  /**
   * @brief Equality operator
   * @param vec vector_2f object
   * @return bool
   */
  bool operator==(const vector_2f &vec) const noexcept;

  /**
   * @brief Division operator
   * @param scalar scalar value
   * @return vector_2f
   */
  vector_2f operator/(float scalar) const noexcept;

  /**
   * @brief Division assignment operator
   * @param scalar scalar value
   * @return vector_2f&
   */
  vector_2f &operator/=(float scalar) noexcept;

  /**
   * @brief Get the zero vector
   * @return vector_2f
   */
  static constexpr vector_2f zero() noexcept { return {0, 0}; }

  /**
   * @brief Get the one vector
   * @return
   */
  static constexpr vector_2f one() noexcept { return {1, 1}; }

  /**
   * @brief Get the up vector
   * @return
   */
  static constexpr vector_2f up() noexcept { return {0, 1}; }

  /**
   * @brief Get the down vector
   * @return
   */
  static constexpr vector_2f down() noexcept { return {0, -1}; }

  /**
   * @brief Get the left vector
   * @return
   */
  static constexpr vector_2f left() noexcept { return {-1, 0}; }

  /**
   * @brief Get the right vector
   * @return
   */
  static constexpr vector_2f right() noexcept { return {1, 0}; }

  /**
   * @brief Dot product
   * @param vec1 vector_2f object
   * @param vec2 vector_2f object
   * @return dot product
   */
  [[nodiscard]] static float dot(const vector_2f &vec1, const vector_2f &vec2) noexcept;

  /**
   * @brief Distance between two vectors
   * @param vec1 vector_2f object
   * @param vec2 vector_2f object
   * @return distance
   */
  [[nodiscard]] static double distance(const vector_2f &vec1, const vector_2f &vec2) noexcept;

  /**
   * @brief Normalize a vector
   * @param vec vector_2f object
   * @return normalized vector
   */
  [[nodiscard]] vector_2f normalize(const vector_2f &vec) const noexcept;

  /**
   * @brief Throw if vector has negative values
   * @param vec vector_2f object
   */
  static void throw_if_negative(vector_2f const &vec);

 public:
  /// @brief x value
  float x{0};
  /// @brief y value
  float y{0};
};
}  // namespace zygarde::core::types
