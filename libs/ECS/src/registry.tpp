/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.tpp
*/

#pragma once
#include <stdexcept>

using namespace rtype::sdk::ECS;

template <typename Component>
sparse_array<Component> &Registry::registerComponent() {
  const auto type_idx = std::type_index(typeid(Component));

  auto [it, inserted] =
      components_arrays_.try_emplace(typeid(Component), sparse_array<Component>());

  if (!inserted) {
    return std::any_cast<sparse_array<Component> &>(it->second);
  }

  remove_functions_[type_idx] =
      ([](Registry &reg, const Entity &e) { reg.removeComponent<Component>(e); });

  return std::any_cast<sparse_array<Component> &>(components_arrays_[type_idx]);
}

template <typename Component>
sparse_array<Component> &Registry::getComponents() {
  return std::any_cast<sparse_array<Component> &>(components_arrays_[typeid(Component)]);
}

template <typename Component>
const sparse_array<Component> &Registry::getComponents() const {
  return std::any_cast<sparse_array<Component> &>(components_arrays_.at(typeid(Component)));
}

template <typename Component>
typename sparse_array<Component>::reference_type Registry::addComponent(Entity const &to,
                                                                        Component &&c) {
  auto &components = getComponents<Component>();
  const auto size = components.size();

  if (size <= to.id_) {
    components.resize(static_cast<size_t>(to) + 1);
  }
  if (max_components_length_ < size) {
    max_components_length_ = size;
  }
  return components.emplaceAt(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename sparse_array<Component>::reference_type Registry::emplaceComponent(Entity const &to,
                                                                            Params &&...p) {
  auto &components = getComponents<Component>();

  return components.emplaceAt(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void Registry::removeComponent(Entity const &from) {
  auto &components = getComponents<Component>();

  components.erase(static_cast<size_t>(from));
}

template <class... Components, typename Function>
void Registry::addSystem(Function &&f) {
  systems_.push_back(
      [this, f = std::forward<Function>(f)]() { f(*this, getComponents<Components>()...); });
}
