/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** currentHealth.cpp
*/

#include "health_update.hpp"

using namespace rtype::sdk::api_common::payload;

HealthUpdate::HealthUpdate(std::size_t entityId, std::size_t currentHealth)
    : entityId{entityId}, currentHealth{currentHealth} {}
