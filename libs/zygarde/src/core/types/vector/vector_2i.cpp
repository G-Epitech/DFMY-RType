/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2f.cpp
*/

#include "./vector_2i.hpp"

#include <stdexcept>

using namespace zygarde::core::types;

Vector2i Vector2i::operator+(const Vector2i& vec) const noexcept {
  return {this->y + vec.y, this->x + vec.x};
}

Vector2i Vector2i::operator-(const Vector2i& vec) const noexcept {
  return {this->y - vec.y, this->x - vec.x};
}

Vector2i& Vector2i::operator+=(const Vector2i& vec) noexcept {
  return *this = *this + vec;
}

Vector2i& Vector2i::operator-=(const Vector2i& vec) noexcept {
  return *this = *this - vec;
}

Vector2i Vector2i::operator*(int scalar) const noexcept {
  return {this->x * scalar, this->y * scalar};
}

Vector2i& Vector2i::operator*=(float scalar) noexcept {
  return *this = *this * scalar;
}

Vector2i Vector2i::operator*(const Vector2i& vec) const noexcept {
  return {this->x * vec.x, this->y * vec.y};
}

Vector2i& Vector2i::operator*=(const Vector2i& vec) noexcept {
  return *this = *this * vec;
}

bool Vector2i::operator==(const Vector2i& vec) const noexcept {
  return this->x == vec.x && this->y == vec.y;
}

Vector2i Vector2i::operator/(float scalar) const noexcept {
  return scalar == 0 ? Vector2i() : Vector2i(this->x / scalar, this->y / scalar);
}

Vector2i& Vector2i::operator/=(float scalar) noexcept {
  return *this = *this / scalar;
}

float Vector2i::dot(const Vector2i& vec1, const Vector2i& vec2) noexcept {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

double Vector2i::distance(const Vector2i& vec1, const Vector2i& vec2) noexcept {
  return std::sqrt(std::pow(vec2.x - vec1.x, 2) + std::pow(vec2.y - vec1.y, 2));
}

Vector2i Vector2i::normalize(const Vector2i& vec) const noexcept {
  return *this / static_cast<float>(std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)));
}

float Vector2i::magnitude() const noexcept {
  return std::sqrt(x * x + y * y);
}

Vector2i Vector2i::normalized() const noexcept {
  return *this / magnitude();
}

zygarde::core::types::Vector2i operator*(float scalar,
                                         const zygarde::core::types::Vector2i& vec) noexcept {
  return vec * scalar;
}
