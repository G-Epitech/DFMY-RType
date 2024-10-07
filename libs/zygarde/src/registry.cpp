/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "registry.hpp"

using namespace zygarde;

Registry::Registry(Private) {}

std::shared_ptr<Registry> Registry::create() {
  return std::make_shared<Registry>(Private());
}

std::shared_ptr<Registry> Registry::GetShared() {
  return shared_from_this();
}

void Registry::RunSystems() {
  const auto pt = GetShared();
  for (const auto &system : systems_) {
    (*system)(pt);
  }
}

Entity Registry::SpawnEntity() {
  if (!freeIds_.empty()) {
    const auto id = freeIds_.top();
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

Registry::Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Registry::Exception::what() const noexcept {
  return message_.c_str();
}
