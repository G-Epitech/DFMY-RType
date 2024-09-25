/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.cpp
*/

#include "entity.hpp"

using namespace rtype;

Entity::Entity(const std::size_t idx) : _id{idx} {}

Entity::operator std::size_t() const {
  return _id;
}
