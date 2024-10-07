/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2_f.cpp
*/

#include "vector_2f.hpp"

#include <stdexcept>

using namespace zygarde::core::types;

constexpr vector_2f::vector_2f() : x(0), y(0) {}

constexpr vector_2f::vector_2f(float x, float y) : x(x), y(y) {}

vector_2f vector_2f::operator+(const vector_2f& vec) const noexcept {
  return {this->y + vec.y, this->x + vec.x};
}

vector_2f vector_2f::operator-(const vector_2f& vec) const noexcept {
  return {this->y - vec.y, this->x - vec.x};
}

vector_2f& vector_2f::operator+=(const vector_2f& vec) noexcept {
  return *this = *this + vec;
}

vector_2f& vector_2f::operator-=(const vector_2f& vec) noexcept {
  return *this = *this - vec;
}

vector_2f vector_2f::operator*(float scalar) const noexcept {
  return {this->x * scalar, this->y * scalar};
}

vector_2f& vector_2f::operator*=(float scalar) noexcept {
  return *this = *this * scalar;
}

vector_2f vector_2f::operator*(const vector_2f& vec) const noexcept {
  return {this->x * vec.x, this->y * vec.y};
}

vector_2f& vector_2f::operator*=(const vector_2f& vec) noexcept {
  return *this = *this * vec;
}

bool vector_2f::operator==(const vector_2f& vec) const noexcept {
  return this->x == vec.x && this->y == vec.y;
}

vector_2f vector_2f::operator/(float scalar) const noexcept {
  return scalar == 0 ? vector_2f() : vector_2f(this->x / scalar, this->y / scalar);
}

vector_2f& vector_2f::operator/=(float scalar) noexcept {
  return *this = *this / scalar;
}

float vector_2f::dot(const vector_2f& vec1, const vector_2f& vec2) noexcept {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

double vector_2f::distance(const vector_2f& vec1, const vector_2f& vec2) noexcept {
  return std::sqrt(std::pow(vec2.x - vec1.x, 2) + std::pow(vec2.y - vec1.y, 2));
}

vector_2f vector_2f::normalize(const vector_2f& vec) const noexcept {
  return *this / static_cast<float>(std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)));
}

void vector_2f::throw_if_negative(const vector_2f& vec) {
  if (vec.x < 0 || vec.y < 0) {
    throw std::invalid_argument("Vector should be positive");
  }
}
