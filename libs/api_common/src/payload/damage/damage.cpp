/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** newHp.cpp
*/

#include "damage.hpp"

using namespace rtype::sdk::api_common::payload;

DamageDealt::DamageDealt(std::size_t entityId, std::size_t newHp)
    : entityId{entityId}, newHp{newHp} {}
