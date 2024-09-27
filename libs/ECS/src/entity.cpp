/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.cpp
*/

#include "entity.hpp"

using namespace rtype::sdk::ECS;

Entity::Entity(const std::size_t idx) : id_{idx} {}

Entity::~Entity() = default;

Entity::operator std::size_t() const {
  return id_;
}
