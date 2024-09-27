/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.tpp
*/

#pragma once

using namespace rtype::sdk::ECS;

template <typename Component>
SparseArray<Component> &Registry::RegisterComponent() {
  const auto type_idx = std::type_index(typeid(Component));

  components_arrays_[type_idx] = SparseArray<Component>();

  remove_functions_.push_back([](Registry &reg, const Entity &e) {
    auto &component_array = reg.GetComponents<Component>();
    auto index = static_cast<size_t>(e);
    if (index < component_array.Size()) {
      component_array[index] = std::nullopt;
    }
  });

  return std::any_cast<SparseArray<Component> &>(components_arrays_[type_idx]);
}

template <typename Component>
SparseArray<Component> &Registry::GetComponents() {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<SparseArray<Component> &>(components_arrays_.at(type_idx));
}

template <typename Component>
const SparseArray<Component> &Registry::GetComponents() const {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<const SparseArray<Component> &>(components_arrays_.at(type_idx));
}

template <typename Component>
typename SparseArray<Component>::reference_type Registry::AddComponent(Entity const &to,
                                                                       Component &&c) {
  auto &components = GetComponents<Component>();
  const auto size = components.Size();

  if (size <= to.id_) {
    components.Resize(static_cast<size_t>(to) + 1);
  }
  return components.EmplaceAt(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename SparseArray<Component>::reference_type Registry::EmplaceComponent(Entity const &to,
                                                                           Params &&...p) {
  auto &components = GetComponents<Component>();

  return components.EmplaceAt(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void Registry::RemoveComponent(Entity const &from) {
  auto &components = GetComponents<Component>();

  components.erase(static_cast<size_t>(from));
}

template <class... Components, typename Function>
void Registry::AddSystem(Function &&f) {
  systems_.push_back(
      [this, f = std::forward<Function>(f)]() { f(*this, GetComponents<Components>()...); });
}
