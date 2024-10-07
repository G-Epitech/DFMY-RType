/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** rigidybody_2_d.cpp
*/

#include "rigidbody_2d.hpp"

using namespace rtype::sdk::ECS::physics::components;

void Rigidbody2D::AddForce(core::types::vector_2f force) noexcept {
  velocity_ += force;
}

void Rigidbody2D::AddForce(float x, float y) noexcept {
  velocity_ += {x, y};
}
