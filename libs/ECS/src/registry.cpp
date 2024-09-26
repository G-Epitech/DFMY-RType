/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include <stdexcept>

#include "registry.hpp"

using namespace rtype::sdk::ECS;

Entity registry::spawn_entity() {
  if (!free_ids.empty()) {
    const Entity new_entity = free_ids.front();
    free_ids.pop_front();
    return new_entity;
  }
  return Entity(max_entity_id++);
}

Entity registry::entity_from_index(const std::size_t idx) const {
  if (idx >= max_entity_id) {
    throw std::out_of_range("entity_from_index: Index is out of range.");
  }
  return Entity(idx);
}

void registry::kill_entity(Entity const &e) {
  free_ids.push_back(e);
  for (auto &remove_function : remove_functions) {
    remove_function(*this, e);
  }
}

void registry::run_systems() {
  for (auto &system : systems) {
    system();
  }
}
