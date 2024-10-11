/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** bounding_box_2d.cpp
*/
#include "bounding_box_2d.hpp"

using namespace zygarde::physics::types;

BoundingBox2D::BoundingBox2D(core::types::Vector2f position, core::types::Vector2f size)
    : left(position.x - size.x / 2),
      right(position.x + size.x / 2),
      top(position.y + size.y / 2),
      bottom(position.y - size.y / 2) {}
