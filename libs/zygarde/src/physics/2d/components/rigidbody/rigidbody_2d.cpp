/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rigidbody2D.cpp
*/

#include "rigidbody_2d.hpp"

using namespace zygarde::physics::components;

void Rigidbody2D::AddForce(core::types::Vector2f force) noexcept {
  velocity_ += force;
}

void Rigidbody2D::AddForce(float x, float y) noexcept {
  velocity_ += {x, y};
}
