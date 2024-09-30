/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <map>
#include <stack>
#include <typeindex>

#include "entity.hpp"
#include "tools/spare_array.hpp"

namespace rtype::sdk::ECS {

/**
 * @brief Registry class
 * This class is used to store all the entities and components
 */
EXPORT_ECS_SDK_API class Registry {
 public:
  /**
   * @brief Register a component
   * @tparam Component Component to register
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &registerComponent();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &getComponents();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return const sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> const &getComponents() const;

  /**
   * @brief Spawn an entity
   * @return Entity
   */
  Entity spawnEntity();

  /**
   * @brief Get an entity from an index
   * @param idx Index of the entity
   * @return Entity
   */
  [[nodiscard]] EXPORT_ECS_SDK_API Entity entityFromIndex(std::size_t idx) const;

  /**
   * @brief Kill an entity
   * @param e Entity to kill
   */
  void killEntity(Entity const &e);

  /**
   * @brief Add a component to an entity
   * @tparam Component Component to add
   * @param to Entity to add the component to
   * @param c Component to add
   */
  template <typename Component>
  typename sparse_array<Component>::reference_type addComponent(Entity const &to, Component &&c);

  /**
   * @brief Emplace a component to an entity
   * @tparam Component Component to add
   * @tparam Params Parameters of the component
   * @param to Entity to add the component to
   * @param p Parameters of the component
   */
  template <typename Component, typename... Params>
  typename sparse_array<Component>::reference_type emplaceComponent(Entity const &to,
                                                                    Params &&...p);

  /**
   * @brief Remove a component from an entity
   * @tparam Component Component to remove
   * @param from Entity to remove the component from
   */
  template <typename Component>
  void removeComponent(Entity const &from);

  /**
   * @brief Add a system
   * @tparam Components Components to add
   * @tparam Function Function to add
   * @param f Function to add
   */
  template <class... Components, typename Function>
  void addSystem(Function &&f);

  /**
   * @brief Run all the systems
   */
  void runSystems();

 private:
  /// @brief systems stored
  std::vector<std::function<void()>> systems_;

  /// @brief Components stored with their type
  std::map<std::type_index, std::any> components_arrays_;

  /// @brief Max components length
  size_t max_components_length_ = 0;

  /// @brief Current Max entity id
  size_t current_max_entity_id_ = 0;

  /// @brief Free ids available for entities
  std::stack<Entity> free_ids_;

  /// @brief remove functions used to remove components
  using component_destroyer = std::function<void(Registry &, Entity const &)>;
  std::map<std::type_index, component_destroyer> remove_functions_;
};
}  // namespace rtype::sdk::ECS

#include "registry.tpp"
