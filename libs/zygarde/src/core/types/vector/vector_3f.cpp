/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_3f.cpp
*/

#include "vector_3f.hpp"

using namespace zygarde::core::types;

vector_3f vector_3f::operator+(const vector_3f& other) const noexcept {
  return vector_3f{x + other.x, y + other.y, z + other.z};
}

vector_3f vector_3f::operator-(const vector_3f& other) const noexcept {
  return vector_3f{x - other.x, y - other.y, z - other.z};
}

vector_3f vector_3f::operator*(const vector_3f& other) const noexcept {
  return vector_3f{x * other.x, y * other.y, z * other.z};
}

vector_3f vector_3f::operator/(const vector_3f& other) const noexcept {
  return vector_3f{x / other.x, y / other.y, z / other.z};
}

vector_3f& vector_3f::operator+=(const vector_3f& other) noexcept {
  return *this = *this + other;
}

vector_3f& vector_3f::operator-=(const vector_3f& other) noexcept {
  return *this = *this - other;
}

vector_3f& vector_3f::operator*=(const vector_3f& other) noexcept {
  return *this = *this * other;
}

vector_3f& vector_3f::operator/=(const vector_3f& other) noexcept {
  return *this = *this / other;
}
