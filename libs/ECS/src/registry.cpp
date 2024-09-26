/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "registry.hpp"

#include <stdexcept>

using namespace rtype::sdk::ECS;

Entity registry::spawn_entity() {
  if (!mfree_ids.empty()) {
    const Entity new_entity = mfree_ids.front();
    mfree_ids.pop_front();
    return new_entity;
  }
  return Entity(mcurrent_max_entity_id++);
}

Entity registry::entity_from_index(const std::size_t idx) const {
  if (idx >= mcurrent_max_entity_id) {
    throw std::out_of_range("entity_from_index: Index is out of range.");
  }
  return Entity(idx);
}

void registry::kill_entity(Entity const &e) {
  mfree_ids.push_back(e);
  for (auto &remove_function : mremove_functions) {
    remove_function(*this, e);
  }
}

void registry::run_systems() {
  for (auto &system : msystems) {
    system();
  }
}
