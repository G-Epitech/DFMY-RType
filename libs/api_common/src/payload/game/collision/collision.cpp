/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** collision.cpp
*/

#include "collision.hpp"

using namespace rtype::sdk::api_common::payload;

Collision::Collision(std::size_t entityId1, std::size_t entityId2)
    : entityId1{entityId1}, entityId2{entityId2} {}
