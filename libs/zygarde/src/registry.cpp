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
  std::size_t newId;

  if (!freeIds_.empty()) {
    newId = freeIds_.top();
    freeIds_.pop();
  } else {
    newId = currentMaxEntityId_++;
  }
  Entity e(newId);
  entities_.push_back(e);
  return e;
}

Entity Registry::EntityFromIndex(const std::size_t idx) const {
  return entities_.at(idx);
}

void Registry::KillEntity(Entity const &e) {
  freeIds_.push(static_cast<std::size_t>(e));
  entities_.erase(entities_.begin(), std::remove(entities_.begin(), entities_.end(), e));
  for (auto &remove_function : removeFunctions_) {
    remove_function.second(*this, e);
  }
}

std::size_t Registry::IndexFromEntity(const Entity &e) const {
  for (std::size_t i = 0; i < entities_.size(); i++) {
    if (entities_.at(i) == e) {
      return i;
    }
  }
  throw Exception("Entity not found");
}

Registry::Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Registry::Exception::what() const noexcept {
  return message_.c_str();
}
