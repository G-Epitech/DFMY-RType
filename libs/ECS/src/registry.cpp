/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "registry.hpp"

#include <stdexcept>

using namespace rtype::sdk::ECS;

Entity Registry::spawnEntity() {
  if (!free_ids_.empty()) {
    const Entity new_entity = free_ids_.top();
    free_ids_.pop();
    return new_entity;
  }
  return Entity(current_max_entity_id_++);
}

Entity Registry::entityFromIndex(const std::size_t idx) const {
  if (idx >= current_max_entity_id_ || max_components_length_ <= idx) {
    throw std::out_of_range("entity_from_index: Index is out of range.");
  }
  return Entity(idx);
}

void Registry::killEntity(Entity const &e) {
  free_ids_.push(e);
  for (auto &remove_function : remove_functions_) {
    remove_function.second(*this, e);
  }
}

void Registry::runSystems() {
  for (auto &system : systems_) {
    system();
  }
}
