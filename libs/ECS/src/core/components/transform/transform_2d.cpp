/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** transform.cpp
*/

#include "transform_2d.hpp"

using namespace rtype::sdk::ECS::core::components;

Transform2D::Transform2D(float x, float y, float scale_x, float scale_y, float rotation)
    : position(x, y), scale(scale_x, scale_y), rotation(rotation)
{
}

Transform2D::Transform2D(const types::vector_2f &position, const types::vector_2f &scale, float rotation)
    : position(position), scale(scale), rotation(rotation)
{
}
