/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2_f.cpp
*/

#include "./vector_2f.hpp"

#include <stdexcept>

using namespace zygarde::core::types;

Vector2f Vector2f::operator+(const Vector2f& vec) const noexcept {
  return {this->y + vec.y, this->x + vec.x};
}

Vector2f Vector2f::operator-(const Vector2f& vec) const noexcept {
  return {this->y - vec.y, this->x - vec.x};
}

Vector2f& Vector2f::operator+=(const Vector2f& vec) noexcept {
  return *this = *this + vec;
}

Vector2f& Vector2f::operator-=(const Vector2f& vec) noexcept {
  return *this = *this - vec;
}

Vector2f Vector2f::operator*(float scalar) const noexcept {
  return {this->x * scalar, this->y * scalar};
}

Vector2f& Vector2f::operator*=(float scalar) noexcept {
  return *this = *this * scalar;
}

Vector2f Vector2f::operator*(const Vector2f& vec) const noexcept {
  return {this->x * vec.x, this->y * vec.y};
}

Vector2f& Vector2f::operator*=(const Vector2f& vec) noexcept {
  return *this = *this * vec;
}

bool Vector2f::operator==(const Vector2f& vec) const noexcept {
  return this->x == vec.x && this->y == vec.y;
}

Vector2f Vector2f::operator/(float scalar) const noexcept {
  return scalar == 0 ? Vector2f() : Vector2f(this->x / scalar, this->y / scalar);
}

Vector2f& Vector2f::operator/=(float scalar) noexcept {
  return *this = *this / scalar;
}

float Vector2f::dot(const Vector2f& vec1, const Vector2f& vec2) noexcept {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

double Vector2f::distance(const Vector2f& vec1, const Vector2f& vec2) noexcept {
  return std::sqrt(std::pow(vec2.x - vec1.x, 2) + std::pow(vec2.y - vec1.y, 2));
}

Vector2f Vector2f::normalize(const Vector2f& vec) const noexcept {
  return *this / static_cast<float>(std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)));
}

void Vector2f::throw_if_negative(const Vector2f& vec) {
  if (vec.x < 0 || vec.y < 0) {
    throw std::invalid_argument("Vector should be positive");
  }
}
