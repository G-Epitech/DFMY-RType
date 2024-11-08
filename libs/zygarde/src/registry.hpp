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
#include <memory>
#include <stack>
#include <string>
#include <typeindex>

#include "./entity.hpp"
#include "./system_interface.hpp"
#include "./tools/spare_array.hpp"
#include "./tools/zipper.hpp"

namespace zygarde {

/**
 * @brief Registry class
 * This class is used to store all the entities and components
 */
class EXPORT_ZYGARDE_API Registry : public std::enable_shared_from_this<Registry> {
 private:
  struct Private {
    Private() = default;
  };

 public:
  using Ptr = std::shared_ptr<Registry>;
  using Const_Ptr = const std::shared_ptr<Registry> &;

  /**
   * @brief Construct a new Registry object
   */
  explicit Registry(Private);

  /**
   * @brief Create a new registry.
   * @return std::shared_ptr<Registry>
   */
  static std::shared_ptr<Registry> Create();

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
  template <typename Component>
  typename sparse_array<Component>::ptr RegisterComponent();

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return const sparse_array<Component>&
   */
  template <typename Component>
  typename sparse_array<Component>::ptr GetComponents() const;

  /**
   * @brief Get the components
   * @tparam Component Component to get
   * @return const sparse_array<Component>&
   */
  template <typename Component>
  std::optional<Component *> GetComponent(Entity const &e);

  /**
   * @brief Spawn an entity with a specific type
   * @tparam T Type of the entity
   * @return Entity
   */
  template <EntityType T = Entity, typename... Args>
  Entity SpawnEntity(Args &&...args);

  /**
   * @brief Get an entity from an index
   * @param idx Index of the entity
   * @return Entity
   */
  [[nodiscard]] Entity EntityFromIndex(std::size_t idx) const;

  /**
   * @brief Check if an entity exists at an index
   * @param idx Index to check
   * @return bool
   */
  [[nodiscard]] bool HasEntityAtIndex(std::size_t idx) const;

  /**
   * @brief Kill an entity
   * @param e Entity to kill
   */
  void KillEntity(Entity const &e);

  /**
   * @brief Destroy an entity
   * @param e Entity to destroy
   */
  void DestroyEntity(Entity const &e);

  /**
   * @brief Get the entities
   * @return std::vector<std::optional<Entity>>&
   */
  [[nodiscard]] std::vector<std::optional<Entity>> &GetEntities();

  /**
   * @brief Get the entities matching the components
   * @tparam Components Components to match
   * @return Zipped components
   */
  template <typename... Components>
  [[nodiscard]] zipper<Components...> GetMatchingEntities();

  /**
   * @brief Check if an entity has a component
   * @tparam Component Component(s) to check
   * @param e Entity to check
   * @return bool
   */
  template <typename... Component>
  bool HasComponents(Entity const &e);

  /**
   * @brief Cleanup destroyed entities
   */
  void CleanupDestroyedEntities();

  /**
   * @brief Add a component to an entity
   * @tparam Component Component to add
   * @param to Entity to add the component to
   * @param c Component to add
   */
  template <typename Component>
  typename sparse_array<Component>::reference_type AddComponent(Entity const &to, Component &&c);

  /**
   * @brief Add a component to an entity
   * @tparam Component Component to add
   * @param to Entity to add the component to
   * @param c Component to add
   */
  template <typename Component>
  typename sparse_array<Component>::reference_type AddComponent(Entity const &to,
                                                                const Component &c);

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

  /**
   * @brief Get the entities to kill (for cleanup)
   * @return The entities to kill
   */
  [[nodiscard]] inline const std::list<Entity> &GetEntitiesToKill() { return entitiesToKill_; }

 private:
  /// @brief systems stored
  std::vector<std::shared_ptr<ISystem>> systems_;

  /// @brief Components stored with their type
  std::map<std::type_index, std::any> componentsArrays_;

  /// @brief Current Max entity id
  size_t currentMaxEntityId_ = 0;

  /// @brief Entities stored
  std::vector<std::optional<Entity>> entities_;

  /// @brief Free ids available for entities
  std::stack<std::size_t> freeIds_;

  /// @brief Entities to kill
  std::list<Entity> entitiesToKill_;

  /// @brief remove functions used to remove components
  using component_destroyer = std::function<void(Registry &, Entity const &)>;

  /// @brief remove functions used to remove components
  std::map<std::type_index, component_destroyer> removeFunctions_;
};
}  // namespace zygarde

#include "./entity.tpp"
#include "./registry.tpp"
