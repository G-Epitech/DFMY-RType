/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rigidbody2D.cpp
*/

#include "./rigidbody_2d.hpp"

using namespace zygarde::physics::components;

Rigidbody2D::Rigidbody2D(core::types::Vector2f velocity) noexcept : velocity_{velocity} {}

Rigidbody2D::Rigidbody2D(zygarde::core::types::Vector2f velocity, bool isKinematic,
                         float drag) noexcept
    : velocity_{velocity}, isKinematic_{isKinematic}, drag_(drag) {}

void Rigidbody2D::AddForce(core::types::Vector2f force) noexcept {
  velocity_ += force;
}

void Rigidbody2D::AddForce(float x, float y) noexcept {
  velocity_ += {x, y};
}
