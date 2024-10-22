/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** managers_provider.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <map>
#include <memory>
#include <typeindex>

#include "libs/porygon/src/utils/symbols.hpp"

namespace porygon {
class DependenciesHandler;

template <typename T, typename... Args>
concept ConstructibleWithDependenciesHandlerPtr =
    std::is_constructible_v<T, std::shared_ptr<DependenciesHandler>, Args...>;

class DependenciesHandler final : public std::enable_shared_from_this<DependenciesHandler> {
 private:
  struct Private {
    Private() = default;
  };

 public:
  /// @brief Shared pointer of the registry
  using Ptr = std::shared_ptr<DependenciesHandler>;

  /**
   * @brief Construct a new Managers Provider object
   */
  explicit DependenciesHandler(Private);

  /**
   * @brief Create a new Managers Provider object
   * @return Pointer on the created Managers Provider
   */
  static Ptr Create();

  /**
   * @brief Get the shared pointer of this registry.
   * @return std::shared_ptr<Registry>
   */
  Ptr GetShared();

 public:
  /**
   * @brief Build a new DependenciesHandler
   */
  DependenciesHandler() = default;

  /**
   * @brief Destroy the DependenciesHandler
   */
  ~DependenciesHandler() = default;

  /**
   * @brief Build an instance of desired type by injecting dependencies if needed
   * @tparam T Type of the instance to build
   * @tparam Args Arguments types to pass to the constructor
   * @param args Arguments to pass to the constructor
   * @return Built instance
   */
  template <typename T, typename... Args>
  T MakeWithDependencies(Args &&...args);

  /**
   * @brief Build an instance of desired type by injecting dependencies if needed
   * @tparam T Type of the instance to build
   * @tparam Args Arguments types to pass to the constructor
   * @param args Arguments to pass to the constructor
   * @return Built instance
   */
  template <typename T, typename... Args>
  std::shared_ptr<T> MakeSharedWithDependencies(Args &&...args);

  /**
   * @brief Add a manager to the provider
   * @tparam T Manager type
   * @tparam Args Arguments types to pass to the manager constructor
   * @param args Arguments to pass to the manager constructor
   * @return Current provider
   */
  template <typename T, typename... Args>
  DependenciesHandler &Add(Args &&...args);

  /**
   * @brief Add a manager instance to the provider
   * @tparam T Manager type
   * @param instance Instance of the manager
   * @return Current provider
   */
  template <typename T>
  DependenciesHandler &AddInstance(std::shared_ptr<T> instance);

  /**
   * @brief Get a dependency from the provider
   * @tparam T Dependency type
   * @return Manager instance
   */
  template <typename T>
  std::shared_ptr<T> Get();

  /**
   * @brief Get a dependency from the provider or throw an exception if not found
   * @tparam T Dependency type
   * @return Dependency instance
   */
  template <typename T>
  std::shared_ptr<T> GetOrThrow();

 protected:
  /// @brief Map of managers
  typedef std::map<std::type_index, std::shared_ptr<void>> ManagersMap;

  /// @brief Manager builder
  typedef std::function<std::shared_ptr<void>()> ManagerBuilder;

  /// @brief Managers builders map
  typedef std::map<std::type_index, ManagerBuilder> ManagersBuildersMap;

  /// @brief Instances of managers
  ManagersMap instances_;

  /// @brief Builders of managers
  ManagersBuildersMap builders_;

  /**
   * @brief Get an instance of a manager
   * @tparam T Manager type
   * @return Found instance or nullptr
   */
  template <typename T>
  std::shared_ptr<T> GetInstance();

  /**
   * @brief Build an instance of a manager
   * @tparam T Manager type
   * @return Created instance
   */
  template <typename T>
  std::shared_ptr<T> BuildInstance();
};
}  // namespace mew::di

#include "./handler.tpp"
