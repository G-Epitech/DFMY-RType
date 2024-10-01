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
sparse_array<Component> &Registry::RegisterComponent() {
  const auto type_idx = std::type_index(typeid(Component));

  auto [it, inserted] = componentsArrays_.try_emplace(typeid(Component), sparse_array<Component>());

  if (!inserted) {
    return std::any_cast<sparse_array<Component> &>(it->second);
  }

  removeFunctions_[type_idx] =
      ([](Registry &reg, const Entity &e) { reg.RemoveComponent<Component>(e); });

  return std::any_cast<sparse_array<Component> &>(componentsArrays_[type_idx]);
}

template <typename Component>
sparse_array<Component> &Registry::GetComponents() {
  if (!componentsArrays_.contains(typeid(Component))) {
    throw Exception("Component not registered");
  }
  return std::any_cast<sparse_array<Component> &>(componentsArrays_[typeid(Component)]);
}

template <typename Component>
const sparse_array<Component> &Registry::GetComponents() const {
  if (!componentsArrays_.contains(typeid(Component))) {
    throw Exception("Component not registered");
  }
  return std::any_cast<sparse_array<Component> &>(componentsArrays_.at(typeid(Component)));
}

template <typename Component>
typename sparse_array<Component>::reference_type Registry::AddComponent(Entity const &to,
                                                                        Component &&c) {
  auto &components = GetComponents<Component>();
  const auto size = components.size();

  if (size <= to.id_) {
    components.resize(static_cast<size_t>(to) + 1);
  }
  return components.emplaceAt(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename sparse_array<Component>::reference_type Registry::EmplaceComponent(Entity const &to,
                                                                            Params &&...p) {
  auto &components = GetComponents<Component>();

  return components.emplaceAt(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void Registry::RemoveComponent(Entity const &from) {
  auto &components = GetComponents<Component>();

  components.erase(static_cast<size_t>(from));
}

template <typename System, typename... ExtraParams>
void Registry::AddSystem(ExtraParams &&...extraParams) {
  systems_.push_back(std::make_shared<System>(std::forward<ExtraParams>(extraParams)...));
}
