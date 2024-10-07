/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2_f.cpp
*/

#include "vector_2f.hpp"

using namespace rtype::sdk::ECS::core::types;

vector_2f::vector_2f(float x, float y) : x(x), y(y) {}

vector_2f vector_2f::operator+(const vector_2f& vec) const {
  return {this->y + vec.y, this->x + vec.x};
}

vector_2f vector_2f::operator-(const vector_2f& vec) const {
  return {this->y - vec.y, this->x - vec.x};
}
vector_2f& vector_2f::operator+=(const vector_2f& vec) {
  return *this = *this + vec;
}
vector_2f vector_2f::operator-=(const vector_2f& vec) {
  return *this = *this - vec;
}
