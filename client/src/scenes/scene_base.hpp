/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.hpp
*/

#pragma once

#include "scene_interface.hpp"

namespace rtype::client {
class SceneBase : public IScene {
 protected:
  /**
   * @brief Build common scene with global context
   * @param global_context Global context provided by the app
   */
  explicit SceneBase(const GlobalContext &global_context);

  /**
   * @brief Destroy the scene
   */
  ~SceneBase() override = default;

  /**
   * @brief Store the global context provided by the app
   */
  const GlobalContext &globalContext_;

 public:
  /***
   * @brief Draw the scene
   */
  void Draw() override;

  /**
   * @brief Update the scene
   * @param delta_time Time since last update
   */
  void Update(utils::DeltaTime delta_time) override;

  /**
   * @brief Called when the scene is created
   */
  void OnCreate() override;

  /**
   * @brief Called when the scene is destroyed
   */
  void OnDestroy() override;

  /**
   * @brief Called when the scene is switched to
   */
  void OnActivate() override;

  /**
   * @brief Called when the scene is switched from
   */
  void OnDeactivate() override;
};
}  // namespace rtype::client
