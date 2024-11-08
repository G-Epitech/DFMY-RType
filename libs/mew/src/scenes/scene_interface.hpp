/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_interface.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <chrono>
#include <memory>

#include "libs/mew/include/api.hpp"
#include "libs/zygarde/src/utils/timer/timer.hpp"

namespace mew::scenes {
class EXPORT_MEW_API IScene {
 public:
  /// @brief Pointer type
  using Ptr = std::shared_ptr<IScene>;

  /// @brief Alias for delta time
  using DeltaTime = zygarde::utils::Timer::Nanoseconds;

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
  virtual void Update(DeltaTime delta_time) = 0;
};

/**
 * @brief Ensure that the type is an implementation of IScene
 * @tparam T Type to check
 */
template <class T>
concept SceneType = std::is_base_of_v<IScene, T>;
}  // namespace mew::scenes
