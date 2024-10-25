/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "./registry.hpp"

using namespace zygarde;

Registry::Registry(Private) {}

std::shared_ptr<Registry> Registry::Create() {
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

Entity Registry::EntityFromIndex(const std::size_t idx) const {
  if (entities_.empty()) {
    throw Exception("Entity not found");
  }
  if (entities_.size() <= idx) {
    throw Exception("Entity not found");
  }
  if (!entities_.at(idx).has_value()) {
    throw Exception("Entity not found");
  }
  return entities_.at(idx).value();
}

void Registry::KillEntity(Entity const &e) {
  if (std::find(entities_.begin(), entities_.end(), e) == entities_.end()) {
    return;
  }
  freeIds_.push(static_cast<std::size_t>(e));
  entities_.at(e.id_) = std::nullopt;
  for (auto &remove_function : removeFunctions_) {
    remove_function.second(*this, e);
  }
}

void Registry::DestroyEntity(const Entity &e) {
  entitiesToKill_.push(e);
}

void Registry::CleanupDestroyedEntities() {
  while (!entitiesToKill_.empty()) {
    KillEntity(entitiesToKill_.top());
    entitiesToKill_.pop();
  }
}
bool Registry::HasEntityAtIndex(std::size_t idx) const {
  return idx < entities_.size() && entities_.at(idx).has_value();
}

Registry::Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Registry::Exception::what() const noexcept {
  return message_.c_str();
}

std::vector<std::optional<Entity>> &Registry::GetEntities() {
  return entities_;
}
