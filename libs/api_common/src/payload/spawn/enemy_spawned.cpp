/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** enemy_spawned.cpp
*/

#include "enemy_spawned.hpp"

using namespace rtype::sdk::api_common::payload;

EnemySpawned::EnemySpawned(std::size_t entityId, utils::types::vector_2f position)
    : entityId{entityId}, position{position} {}
