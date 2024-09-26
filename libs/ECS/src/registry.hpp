/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.hpp
*/

#pragma once

#include <any>
#include <map>
#include <list>
#include <typeindex>
#include <functional>

#include "entity.hpp"
#include "tools/spare_array.hpp"

namespace rtype::sdk::ECS {
class registry {
 public:
  template <class Component>
  sparse_array<Component> &register_component();

  template <class Component>
  sparse_array<Component> &get_components();

  template <class Component>
  sparse_array<Component> const &get_components() const;

  Entity spawn_entity();

  Entity entity_from_index(std::size_t idx) const;

  void kill_entity(Entity const &e);

  template <typename Component>
  typename sparse_array<Component>::reference_type add_component(Entity const &to, Component &&c);

  template <typename Component, typename... Params>
  typename sparse_array<Component>::reference_type emplace_component(Entity const &to,
                                                                     Params &&...p);

  template <typename Component>
  void remove_component(Entity const &from);

  template <class... Components, typename Function>
  void add_system(Function &&f);

  void run_systems();

 private:
  std::vector<std::function<void()> > systems;
  std::map<std::type_index, std::any> _component_arrays;
  size_t max_entity_id = 0;
  std::list<Entity> free_ids;
  std::vector<std::function<void(registry &, const Entity &)> > remove_functions;
  std::unordered_map<std::type_index, std::any> _components_arrays;
};
}  // namespace rtype::sdk::ECS

#include "registry.tpp"
