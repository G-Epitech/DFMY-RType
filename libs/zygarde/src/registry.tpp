/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.tpp
*/

#pragma once

#include <stdexcept>

#include "./utils/symbols.hpp"

using namespace zygarde;

template <typename Component>
typename sparse_array<Component>::ptr Registry::RegisterComponent() {
  const auto type_idx = std::type_index(typeid(Component));

  auto [it, inserted] =
      componentsArrays_.try_emplace(typeid(Component), std::make_shared<sparse_array<Component>>());

  if (!inserted) {
    return std::any_cast<typename sparse_array<Component>::ptr>(it->second);
  }

  removeFunctions_[type_idx] =
      ([](Registry &reg, const Entity &e) { reg.RemoveComponent<Component>(e); });

  return std::any_cast<typename sparse_array<Component>::ptr>(componentsArrays_[type_idx]);
}

template <typename Component>
typename sparse_array<Component>::ptr Registry::GetComponents() const {
  try {
    auto components = componentsArrays_.at(typeid(Component));
    return std::any_cast<typename sparse_array<Component>::ptr>(components);
  } catch (std::out_of_range &) {
    throw Exception("Component not registered: " + utils::GetTypeName<Component>() + ".");
  }
}

template <typename Component>
Component *Registry::GetComponent(const Entity &e) {
  typename sparse_array<Component>::ptr components = GetComponents<Component>();
  if (!components) {
    return nullptr;
  }

  if (components->size() > e.id_) {
    auto &optionalComponent = (*components)[e.id_];
    if (optionalComponent) {
      return &(*optionalComponent);
    }
  }
  return nullptr;
}

template <typename Component>
typename sparse_array<Component>::reference_type Registry::AddComponent(Entity const &to,
                                                                        Component &&c) {
  auto components = GetComponents<Component>();
  const auto size = components->size();

  if (size <= to.id_) {
    components->resize(static_cast<size_t>(to) + 1);
  }
  return components->emplaceAt(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename sparse_array<Component>::reference_type Registry::EmplaceComponent(Entity const &to,
                                                                            Params &&...p) {
  auto components = GetComponents<Component>();

  return components->emplaceAt(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void Registry::RemoveComponent(Entity const &from) {
  auto components = GetComponents<Component>();

  components->erase(static_cast<size_t>(from));
}

template <typename System, typename... ExtraParams>
void Registry::AddSystem(ExtraParams &&...extraParams) {
  systems_.push_back(std::make_shared<System>(std::forward<ExtraParams>(extraParams)...));
}

template <typename... Components>
bool Registry::HasComponents(Entity const &e) {
  return (... && (GetComponent<Components>(e) != nullptr));
}

template <EntityType T, typename... Args>
Entity Registry::SpawnEntity(Args &&...args) {
  std::size_t newId;

  if (!freeIds_.empty()) {
    newId = freeIds_.top();
    freeIds_.pop();
  } else {
    newId = currentMaxEntityId_++;
  }
  if (newId >= entities_.size()) {
    entities_.resize(newId + 1);
  }
  T e(newId, *this, std::forward<Args>(args)...);
  entities_.at(newId) = e;
  e.OnSpawn();
  return e;
}
