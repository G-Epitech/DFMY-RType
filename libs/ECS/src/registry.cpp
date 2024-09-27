/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "registry.hpp"

#include <stdexcept>

using namespace rtype::sdk::ECS;

Entity Registry::SpawnEntity() {
  if (!free_ids_.empty()) {
    const Entity new_entity = free_ids_.front();
    free_ids_.pop_front();
    return new_entity;
  }
  return Entity(current_max_entity_id_++);
}

Entity Registry::EntityFromIndex(const std::size_t idx) const {
  if (idx >= current_max_entity_id_) {
    throw std::out_of_range("entity_from_index: Index is out of range.");
  }
  return Entity(idx);
}

void Registry::KillEntity(Entity const &e) {
  free_ids_.push_back(e);
  for (auto &remove_function : remove_functions_) {
    remove_function(*this, e);
  }
}

void Registry::RunSystems() {
  for (auto &system : systems_) {
    system();
  }
}
