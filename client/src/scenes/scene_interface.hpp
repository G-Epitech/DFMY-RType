/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_interface.hpp
*/

#pragma once

#include <chrono>

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
   * @brief Called when the scene is created
   */
  virtual void OnCreate() = 0;

  /**
   * @brief Called when the scene is destroyed
   */
  virtual void OnDestroy() = 0;

  /**
   * @brief Called when the scene is activated.
   * This is called when the becomes the current scene.
   */
  virtual void OnActivate() = 0;

  /**
   * @brief Called when the scene is deactivated.
   * This is called when the scene is no longer the current scene.
   */
  virtual void OnDeactivate() = 0;

  /**
   * @brief Update the scene
   * @param delta_time Time since the last update
   */
  virtual void Update(std::chrono::nanoseconds delta_time) = 0;

  /**
   * @brief Draw the scene
   */
  virtual void Draw() = 0;
};

/**
 * @brief Ensure that the type is an implementation of IScene
 * @tparam T Type to check
 */
template <class T>
concept SceneType = std::is_base_of_v<IScene, T>;
}  // namespace rtype::client
