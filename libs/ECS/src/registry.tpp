/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.tpp
*/

#pragma once

using namespace rtype::sdk::ECS;

template <typename Component>
sparse_array<Component> &registry::register_component() {
  const auto type_idx = std::type_index(typeid(Component));

  mcomponents_arrays[type_idx] = sparse_array<Component>();

  mremove_functions.push_back([](registry &reg, const Entity &e) {
    auto &component_array = reg.get_components<Component>();
    auto index = static_cast<size_t>(e);
    if (index < component_array.size()) {
      component_array[index] = std::nullopt;
    }
  });

  return std::any_cast<sparse_array<Component> &>(mcomponents_arrays[type_idx]);
}

template <typename Component>
sparse_array<Component> &registry::get_components() {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<sparse_array<Component> &>(mcomponents_arrays.at(type_idx));
}

template <typename Component>
const sparse_array<Component> &registry::get_components() const {
  const auto type_idx = std::type_index(typeid(Component));

  return std::any_cast<const sparse_array<Component> &>(mcomponents_arrays.at(type_idx));
}

template <typename Component>
typename sparse_array<Component>::reference_type registry::add_component(Entity const &to,
                                                                         Component &&c) {
  auto &components = get_components<Component>();
  const auto size = components.size();

  if (size <= to) {
    components.resize(static_cast<size_t>(to) + 1);
  }
  return components.emplace_at(static_cast<size_t>(to), std::forward<Component>(c));
}

template <typename Component, typename... Params>
typename sparse_array<Component>::reference_type registry::emplace_component(Entity const &to,
                                                                             Params &&...p) {
  auto &components = get_components<Component>();

  return components.emplace_at(static_cast<size_t>(to), std::forward<Params>(p)...);
}

template <typename Component>
void registry::remove_component(Entity const &from) {
  auto &components = get_components<Component>();

  components.erase(static_cast<size_t>(from));
}

template <class... Components, typename Function>
void registry::add_system(Function &&f) {
  msystems.push_back(
      [this, f = std::forward<Function>(f)]() { f(*this, get_components<Components>()...); });
}
