/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** entity.cpp
*/

#include "./entity.hpp"

using namespace zygarde;

Entity::Entity(const std::size_t idx, Registry& registry) : id_{idx}, registry_{registry} {}

Entity::~Entity() = default;

Entity::Entity(const Entity& other) = default;

Entity::operator std::size_t() const {
  return id_;
}

std::size_t Entity::GetId() const {
  return id_;
}

Entity& Entity::operator=(const Entity& other) {
  id_ = other.id_;
  return *this;
}

bool Entity::operator==(const Entity& other) const {
  return id_ == other.id_;
}

void Entity::OnSpawn() {}
