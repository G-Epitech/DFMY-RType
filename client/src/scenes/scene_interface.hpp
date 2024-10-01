/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_interface.hpp
*/

#pragma once

#include "context/global_context.hpp"

namespace rtype::client {
class IScene {
 protected:
  friend class ScenesManager;

  /**
   * @brief Inject the global context into the scene
   * @param ctx Context to inject
   */
  virtual void InjectGlobalContext(GlobalContext::Ptr context) = 0;

 public:
  // Pointer type
  using Ptr = std::shared_ptr<IScene>;

  /**
   * @brief Destroy the IScene object
   */
  virtual ~IScene() = default;

  /**
   * @brief Run the scene
   */
  virtual void Run() = 0;
};

/**
 * @brief Ensure that the type is an implementation of IScene
 * @tparam T Type to check
 */
template <class T>
concept SceneType = std::is_base_of_v<IScene, T>;
}  // namespace rtype::client
