/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** movement.cpp
*/

#include "movement.hpp"

using namespace rtype::sdk::api_common::payload;

Movement::Movement(std::size_t entityId, utils::types::vector_2f newPosition)
    : entityId{entityId}, newPosition{newPosition} {}
