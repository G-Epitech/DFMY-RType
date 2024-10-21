/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include "./registry.hpp"

#include <iostream>

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
  entities_.emplace_back(e);
  return e;
}

Entity Registry::EntityFromIndex(const std::size_t idx) const {
  if (entities_.empty()) {
    throw Exception("Entity not found");
  }
  if (entities_.size() < idx) {
    throw Exception("Entity not found");
  }
  if (!entities_.at(idx).has_value()) {
    throw Exception("Entity not found");
  }
  return entities_.at(idx).value();
}

void Registry::KillEntity(Entity const &e) {
  freeIds_.push(static_cast<std::size_t>(e));
  entities_.at(IndexFromEntity(e)) = std::nullopt;
  for (auto &remove_function : removeFunctions_) {
    remove_function.second(*this, e);
  }
}

std::size_t Registry::IndexFromEntity(const Entity &e) const {
  const auto index = e.GetId();
  if (index >= entities_.size()) {
    throw Exception("Entity not found");
  }
  if (!entities_.at(index).has_value()) {
    throw Exception("Entity not found");
  }
  return index;
}

void Registry::DestroyEntity(const Entity &e) {
  entitesToKill_.push(e);
}

void Registry::CleanupDestroyedEntities() {
  while (!entitesToKill_.empty()) {
    KillEntity(entitesToKill_.top());
    entitesToKill_.pop();
  }
}
bool Registry::HasEntityAtIndex(std::size_t idx) const {
  return idx < entities_.size() && entities_.at(idx).has_value();
}

Registry::Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Registry::Exception::what() const noexcept {
  return message_.c_str();
}
