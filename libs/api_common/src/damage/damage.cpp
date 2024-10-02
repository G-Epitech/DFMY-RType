/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** damage.cpp
*/

#include "damage.hpp"

using namespace rtype::sdk::api_common;

DamageDealt::DamageDealt(std::size_t entityId, std::size_t damage)
    : entityId{entityId}, damage{damage} {}
