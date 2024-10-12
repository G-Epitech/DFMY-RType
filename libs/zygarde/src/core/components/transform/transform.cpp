/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** transform.cpp
*/

#include "transform.hpp"

#include <stdexcept>

using namespace zygarde::core::components;

Transform::Transform(zygarde::core::types::Vector3f scale, zygarde::core::types::Vector3f rotation)
    : scale{scale}, rotation{rotation} {
  if (scale.x < 0 || scale.y < 0 || scale.z < 0) {
    throw std::invalid_argument("Scale should be positive");
  }
}
