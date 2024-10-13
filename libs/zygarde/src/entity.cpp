/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** entity.cpp
*/

#include "./entity.hpp"

using namespace zygarde;

Entity::Entity(const std::size_t idx) : id_{idx} {}

Entity::operator std::size_t() const {
  return id_;
}

Entity Entity::operator=(const Entity& other) const {
  return Entity{other.id_};
}

bool Entity::operator==(const Entity& other) const {
  return id_ == other.id_;
}
