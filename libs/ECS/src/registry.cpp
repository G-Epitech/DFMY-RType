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
  if (!freeIds_.empty()) {
    auto id = freeIds_.top();
    freeIds_.pop();
    return Entity(id);
  }
  return Entity(currentMaxEntityId_++);
}

Entity Registry::EntityFromIndex(const std::size_t idx) const {
  if (idx >= currentMaxEntityId_) {
    throw Exception("entity_from_index: Index is out of range.");
  }
  return Entity(idx);
}

void Registry::KillEntity(Entity const &e) {
  freeIds_.push(static_cast<std::size_t>(e));
  for (auto &remove_function : removeFunctions_) {
    remove_function.second(*this, e);
  }
}

void Registry::RunSystems() {
  for (const auto &system : systems_) {
    (*system)(this);
  }
}

Registry::Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Registry::Exception::what() const noexcept {
  return message_.c_str();
}
