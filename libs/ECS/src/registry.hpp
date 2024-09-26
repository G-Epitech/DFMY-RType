/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <list>
#include <map>
#include <typeindex>

#include "entity.hpp"
#include "tools/spare_array.hpp"

namespace rtype::sdk::ECS {

/**
 * @brief Registry class
 * This class is used to store all the entities and components
 */
class registry {
 public:
  /**
   * @brief Register a component
   * @tparam Component Component to register
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &register_component();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &get_components();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return const sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> const &get_components() const;

  /**
   * @brief Spawn an entity
   * @return Entity
   */
  Entity spawn_entity();

  /**
   * @brief Get an entity from an index
   * @param idx Index of the entity
   * @return Entity
   */
  [[nodiscard]] Entity entity_from_index(std::size_t idx) const;

  /**
   * @brief Kill an entity
   * @param e Entity to kill
   */
  void kill_entity(Entity const &e);

  /**
   * @brief Add a component to an entity
   * @tparam Component Component to add
   * @param to Entity to add the component to
   * @param c Component to add
   */
  template <typename Component>
  typename sparse_array<Component>::reference_type add_component(Entity const &to, Component &&c);

  /**
   * @brief Emplace a component to an entity
   * @tparam Component Component to add
   * @tparam Params Parameters of the component
   * @param to Entity to add the component to
   * @param p Parameters of the component
   */
  template <typename Component, typename... Params>
  typename sparse_array<Component>::reference_type emplace_component(Entity const &to,
                                                                     Params &&...p);

  /**
   * @brief Remove a component from an entity
   * @tparam Component Component to remove
   * @param from Entity to remove the component from
   */
  template <typename Component>
  void remove_component(Entity const &from);

  /**
   * @brief Add a system
   * @tparam Components Components to add
   * @tparam Function Function to add
   * @param f Function to add
   */
  template <class... Components, typename Function>
  void add_system(Function &&f);

  /**
   * @brief Run all the systems
   */
  void run_systems();

 private:
  /// @brief systems stored
  std::vector<std::function<void()>> msystems;

  /// @brief Components stored with their type
  std::map<std::type_index, std::any> mcomponents_arrays;

  /// @brief Current Max entity id
  size_t mcurrent_max_entity_id = 0;

  /// @brief Free ids available for entities
  std::list<Entity> mfree_ids;

  /// @brief remove functions used to remove components
  std::vector<std::function<void(registry &, const Entity &)>> mremove_functions;
};
}  // namespace rtype::sdk::ECS

#include "registry.tpp"
