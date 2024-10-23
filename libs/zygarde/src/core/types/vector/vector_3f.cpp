/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Vector3f.cpp
*/

#include "./vector_3f.hpp"

using namespace zygarde::core::types;

Vector3f Vector3f::operator+(const Vector3f& other) const noexcept {
  return Vector3f{x + other.x, y + other.y, z + other.z};
}

Vector3f Vector3f::operator-(const Vector3f& other) const noexcept {
  return Vector3f{x - other.x, y - other.y, z - other.z};
}

Vector3f Vector3f::operator*(const Vector3f& other) const noexcept {
  return Vector3f{x * other.x, y * other.y, z * other.z};
}

Vector3f Vector3f::operator/(const Vector3f& other) const noexcept {
  return Vector3f{x / other.x, y / other.y, z / other.z};
}

Vector3f& Vector3f::operator+=(const Vector3f& other) noexcept {
  return *this = *this + other;
}

Vector3f& Vector3f::operator-=(const Vector3f& other) noexcept {
  return *this = *this - other;
}

Vector3f& Vector3f::operator*=(const Vector3f& other) noexcept {
  return *this = *this * other;
}

Vector3f& Vector3f::operator/=(const Vector3f& other) noexcept {
  return *this = *this / other;
}

bool Vector3f::operator==(const Vector3f& other) const noexcept {
  return x == other.x && y == other.y && z == other.z;
}
