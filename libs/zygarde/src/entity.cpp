/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** entity.cpp
*/

#include "./entity.hpp"

#include <utility>

using namespace zygarde;

Entity::Entity(const std::size_t idx, std::shared_ptr<Registry> registry)
    : id_{idx}, registry_{std::move(registry)} {}

Entity::~Entity() = default;

Entity::Entity(const Entity& other) = default;

Entity::operator std::size_t() const {
  return id_;
}

Entity& Entity::operator=(const Entity& other) = default;

bool Entity::operator==(const Entity& other) const {
  return id_ == other.id_;
}

void Entity::OnSpawn() {}

bool Entity::operator<(const Entity& other) const {
  return id_ < other.id_;
}
