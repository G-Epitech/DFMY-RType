/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** builder.hpp
*/

#pragma once

#include <optional>

#include "./game.hpp"
#include "libs/mew/include/api.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/porygon/src/handler.hpp"

namespace mew::game {

using namespace porygon;

class EXPORT_MEW_API GameBuilder final {
 public:
  /**
   * @brief Construct a new App Builder object
   */
  GameBuilder();
  ~GameBuilder() = default;

  /**
   * @brief Set the properties of the window manager to be created
   * @param properties Properties of the window manager
   * @return Current builder
   */
  GameBuilder &WithWindowProperties(const managers::WindowManager::Properties &properties);

  /**
   * @brief Add a manager to the provider
   * @tparam T Manager type
   * @tparam Args Arguments types to pass to the manager constructor
   * @param args Arguments to pass to the manager constructor
   * @return Current builder
   */
  template <typename T, typename... Args>
  GameBuilder &WithService(Args &&...args);

  /**
   * @brief Add a manager instance to the provider
   * @tparam T Manager type
   * @param instance Manager instance
   * @return Current builder
   */
  template <typename T>
  GameBuilder &WithServiceInstance(std::shared_ptr<T> instance);

  /**
   * @brief Build the application
   * @return Built application
   */
  Game Build();

 private:
  /**
   * @brief Add the default managers to the provider
   */
  managers::GameManagers BuildDefaultManagers();

  /// @brief Store the properties of the window manager to be created
  std::optional<managers::WindowManager::Properties> windowProperties_;

  /// @brief Managers provider
  DependenciesHandler::Ptr services_;
};
}  // namespace mew::game

#include "./builder.tpp"
