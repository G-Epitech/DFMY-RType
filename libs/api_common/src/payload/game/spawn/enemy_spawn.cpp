/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** enemy_spawned.cpp
*/

#include "enemy_spawn.hpp"

using namespace rtype::sdk::api_common::payload;

EnemySpawn::EnemySpawn(std::size_t entityId, utils::types::vector_2f position,
                       game::types::EnemyType enemyType)
    : entityId{entityId}, position{position}, enemyType(enemyType) {}
