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
#include <memory>
#include <stack>
#include <string>
#include <typeindex>

#include "entity.hpp"
#include "system_interface.hpp"
#include "tools/spare_array.hpp"

namespace zygarde {

/**
 * @brief Registry class
 * This class is used to store all the entities and components
 */
class EXPORT_ZYGARDE_API Registry : public std::enable_shared_from_this<Registry> {
 private:
  struct Private {
    explicit Private() = default;
  };

 public:
  explicit Registry(Private);

  /**
   * @brief Create a new registry.
   * @return std::shared_ptr<Registry>
   */
  static std::shared_ptr<Registry> create();

  /**
   * @brief Get the shared pointer of this registry.
   * @return std::shared_ptr<Registry>
   */
  std::shared_ptr<Registry> GetShared();

  /**
   * @brief Register a component
   * @tparam Component Component to register
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &RegisterComponent();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> &GetComponents();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return const sparse_array<Component>&
   */
  template <class Component>
  sparse_array<Component> const &GetComponents() const;

  /**
   * @brief Spawn an entity
   * @return Entity
   */
  Entity SpawnEntity();

  /**
   * @brief Get an entity from an index
   * @param idx Index of the entity
   * @return Entity
   */
  [[nodiscard]] Entity EntityFromIndex(std::size_t idx) const;

  /**
   * @brief Kill an entity
   * @param e Entity to kill
   */
  void KillEntity(Entity const &e);

  /**
   * @brief Add a component to an entity
   * @tparam Component Component to add
   * @param to Entity to add the component to
   * @param c Component to add
   */
  template <typename Component>
  typename sparse_array<Component>::reference_type AddComponent(Entity const &to, Component &&c);

  /**
   * @brief Emplace a component to an entity
   * @tparam Component Component to add
   * @tparam Params Parameters of the component
   * @param to Entity to add the component to
   * @param p Parameters of the component
   */
  template <typename Component, typename... Params>
  typename sparse_array<Component>::reference_type EmplaceComponent(Entity const &to,
                                                                    Params &&...p);

  /**
   * @brief Remove a component from an entity
   * @tparam Component Component to remove
   * @param from Entity to remove the component from
   */
  template <typename Component>
  void RemoveComponent(Entity const &from);

  /**
   * @brief Add a system
   * @param extraParams Extraparams the given function can have
   */
  template <typename System, typename... ExtraParams>
  void AddSystem(ExtraParams &&...extraParams);

  /**
   * @brief Run all the systems
   */
  void RunSystems();

  class EXPORT_ZYGARDE_API Exception final : public std::exception {
   public:
    /**
     * @brief Create a new message when Registry exception
     * @param message The message
     */
    explicit Exception(std::string message);

    /**
     * @brief Get the exception message
     * @return The exception message
     */
    [[nodiscard]] const char *what() const noexcept override;

   private:
    const std::string message_;
  };

  typedef std::shared_ptr<Registry> Ptr;

 private:
  /// @brief systems stored
  std::vector<std::shared_ptr<ISystem>> systems_;

  /// @brief Components stored with their type
  std::map<std::type_index, std::any> componentsArrays_;

  /// @brief Current Max entity id
  size_t currentMaxEntityId_ = 0;

  /// @brief Free ids available for entities
  std::stack<std::size_t> freeIds_;

  /// @brief remove functions used to remove components
  using component_destroyer = std::function<void(Registry &, Entity const &)>;
  std::map<std::type_index, component_destroyer> removeFunctions_;
};
}  // namespace rtype::sdk::ECS

#include "registry.tpp"