/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.tpp
*/

#pragma once

using namespace rtype::sdk::ECS;

template <typename Component>
SparseArray<Component> &registry::RegisterComponent() {
  const auto type_idx = std::type_index(typeid(Component));

  components_arrays_[type_idx] = SparseArray<Component>();

  remove_functions_.push_back([](registry &reg, const Entity &e) {
    auto &component_array = reg.get_components<Component>();
    auto index = static_cast<size_t>(e);
    if (index < component_array.size()) {
      component_array[index] = std::nullopt;
    }
  });

  return std::any_cast<SparseArray<Component> &>(components_arrays_[type_idx]);
}

template <typename Component>
SparseArray<Component> &registry::GetComponents() {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<SparseArray<Component> &>(components_arrays_.at(type_idx));
}

template <typename Component>
const SparseArray<Component> &registry::GetComponents() const {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<const SparseArray<Component> &>(components_arrays_.at(type_idx));
}

template <typename Component>
typename SparseArray<Component>::reference_type registry::AddComponent(Entity const &to,
                                                                         Component &&c) {
  auto &components = get_components<Component>();
  const auto size = components.size();

  if (size <= to.id_) {
    components.resize(static_cast<size_t>(to) + 1);
  }
  return components.emplace_at(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename SparseArray<Component>::reference_type registry::EmplaceComponent(Entity const &to,
                                                                             Params &&...p) {
  auto &components = get_components<Component>();

  return components.emplace_at(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void registry::RemoveComponent(Entity const &from) {
  auto &components = get_components<Component>();

  components.erase(static_cast<size_t>(from));
}

template <class... Components, typename Function>
void registry::AddSystem(Function &&f) {
  systems_.push_back(
      [this, f = std::forward<Function>(f)]() { f(*this, get_components<Components>()...); });
}
