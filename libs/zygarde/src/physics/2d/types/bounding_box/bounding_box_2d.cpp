/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** bounding_box_2d.cpp
*/
#include "bounding_box_2d.hpp"

using namespace zygarde::physics::types;

BoundingBox2D::BoundingBox2D(core::types::Vector2f position, core::types::Vector2f size)
    : left(position.x), right(position.x + size.x), top(position.y), bottom(position.y + size.y) {}
